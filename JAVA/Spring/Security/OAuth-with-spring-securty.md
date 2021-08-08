# 스프링 시큐리티 소셜 로그인 처리

## 의존성 추가 & 설정

### build.gradle

```groovy
dependencies {
    // (...)
    implementation 'org.springframework.boot:spring-boot-starter-oauth2-client'
}
```

### application-oauth.properties

- vcs에 OAuth 인증 키가 노출되지 않게끔 설정 분리

```properties
spring.security.oauth2.client.registration.google.client-id=some-secret-client-id
spring.security.oauth2.client.registration.google.client-secret=some-secret-client-secret
spring.security.oauth2.client.registration.google.scope=email
```

### application.properties

- 분리된 oauth 설정을 읽어올 수 있게끔, profile 추가

```properties
spring.profiles.include=oauth
```

### SecurityConfig.java

- OAuth를 이용한 인증이 활성화 되도록, HttpSecurity 구성 추가

```java
@Configuration
@Slf4j
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    // (...)
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // (...)
        http.oauth2Login();
    }
}
```

### 결과 화면

![localhost_8080_login](https://user-images.githubusercontent.com/18183911/128305549-368b219c-5151-4971-b008-df6ecbea4e47.png)

- but, 서비스에 적용하려면
  - OAuth 인증 이후, 사용자의 이메일 정보(혹은 사용자를 식별할 수 있는 정보)를 추출
  - 서비스의 DB와 연동하여 사용자의 정보 관리
  - UserDetailsService로 구현한 로그인과, OAuth로 구현한 로그인이 동일하게 동작하게끔 처리

## OAuth2UserService <R extends OAuth2UserRequest,​U extends OAuth2User>

- UserDetailsService의 OAuth 버전

### 메서드

- U loadUser(R userRequest)
  - OAuth2AuthenticationException 발생 가능

### 구현체

- CustomUserTypesOAuth2UserService
- DefaultOAuth2UserService
- DelegatingOAuth2UserService
- OidcUserService

### 사용

- OAuth2UserService 인터페이스를 직접 구현하기보다
- DefaultOAuth2UserService 상속하여 재사용하는 것이 구현하기 용이

#### 구현 예시

```java
// ClubOAuthUserDetailsService.java
package io.clroot.club.security.service;

import io.clroot.club.entity.ClubMember;
import io.clroot.club.entity.ClubMemberRole;
import io.clroot.club.repository.ClubMemberRepository;
import io.clroot.club.security.dto.ClubAuthMemberDTO;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.oauth2.client.userinfo.DefaultOAuth2UserService;
import org.springframework.security.oauth2.client.userinfo.OAuth2UserRequest;
import org.springframework.security.oauth2.core.OAuth2AuthenticationException;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional(readOnly = true)
@RequiredArgsConstructor
@Slf4j
public class ClubOAuthUserDetailsService extends DefaultOAuth2UserService {

    private final ClubMemberRepository repository;

    private final PasswordEncoder passwordEncoder;

    @Override
    public OAuth2User loadUser(OAuth2UserRequest userRequest) throws OAuth2AuthenticationException {
        log.info("------------------------------");
        log.info("userRequest: " + userRequest);

        String clientName = userRequest.getClientRegistration().getClientName();

        log.info("clientName: " + clientName);
        log.info(userRequest.getAdditionalParameters().toString());

        OAuth2User oAuth2User = super.loadUser(userRequest);

        log.info("==============================");
        oAuth2User.getAttributes().forEach((k, v) -> {
            log.info(k + ": " + v);
        });

        String email = null;

        if (clientName.equals("Google")) {
            email = oAuth2User.getAttribute("email");
        }

        log.info("EMAIL: " + email);

        ClubMember member = saveSocialMember(email);

        return new ClubAuthMemberDTO(
                member.getEmail(),
                member.getPassword(),
                true,
                member.getRoleSet().stream().map(
                        role -> new SimpleGrantedAuthority("ROLE_" + role)
                ).collect(Collectors.toList()),
                oAuth2User.getAttributes()
        );
    }

    @Transactional
    ClubMember saveSocialMember(String email) {
        Optional<ClubMember> result = repository.findByEmail(email, true);

        if (result.isPresent()) {
            return result.get();
        }

        ClubMember clubMember = ClubMember.builder()
                .email(email)
                .name(email)
                .password(passwordEncoder.encode("1111"))
                .fromSocial(true)
                .build();

        clubMember.addMemberRole(ClubMemberRole.USER);
        repository.save(clubMember);

        return clubMember;
    }
}

```

#### 주의점

- OAuth2UserService의 loadUser()의 경우 OAuth2User(인터페이스) 타입의 객체 반환
- UserDetailsService와 연동을 위해서, UserDetailsService에서 반환하는 타입으로 OAuth2User 타입을 처리할 수 있게끔 구현 필요
  - 예제에서는 ClubAuthMemberDTO 클래스에 OAuth2User 인터페이스를 추가로 구현하여 해결
  - if not, Controller에서 @AuthenticationPrincipal 사용하여 User를 참조하면, OAuth2UserService의 OAuth2User와 호환되지 않아 null로 전달됨

```java
// ClubAuthMemberDTO.java
package io.clroot.club.security.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.oauth2.core.user.OAuth2User;

import java.util.Collection;
import java.util.Map;

@Slf4j
@Getter
@Setter
@ToString
public class ClubAuthMemberDTO extends User implements OAuth2User {

    private String email;

    private String name;

    private boolean fromSocial;

    private Map<String, Object> attr;

    // for UserDetailsService implementation
    public ClubAuthMemberDTO(String username, String password, boolean fromSocial,
                             Collection<? extends GrantedAuthority> authorities) {
        super(username, password, authorities);

        this.email = username;
        this.fromSocial = fromSocial;
    }

    // for DefaultOAuth2UserService implementation
    public ClubAuthMemberDTO(String username, String password, boolean fromSocial,
                             Collection<? extends GrantedAuthority> authorities,
                             Map<String, Object> attr) {
        super(username, password, authorities);

        this.email = username;
        this.fromSocial = fromSocial;
        this.attr = attr;
    }

    @Override
    public Map<String, Object> getAttributes() {
        return this.attr;
    }
}

```
