# 시큐리티를 위한 UserDetailsService

- 스프링 시큐리티에서는 회원, 계정에 대해서 User라는 용어 사용
- 회원을 식별하는 id는 username
- username과 password를 동시에 처리 ❌
  - User의 존재를 확인 한 후
  - password를 검증, 실패시 "bad credentials"
- username과 password 검증 마친 후, URL에 접근할 권한이 있는지 확인 & 인가 진행

## UserDetails 인터페이스

### 메서드

- Collection<? extends GrantedAuthority> getAuthorities()
- String getPassword()
- String getUsername()
- boolean isAccountNonExpired()
- boolean isAccountNonLocked()
- boolean isCredentialsNonExpired()
- boolean isEnabled()

### 구현체

- InetOrgPerson
- LdapUserDetailsImpl
- Person
- User

### 사용

- UserDetails 인터페이스를 직접 구현하기 보다는, 이미 구현된 User 클래스 등을 상속하여 구현하는 것이 더 수월
- User 클래스의 경우, username, password, (Collection<? extends GrantedAuthority>) authorities 이 세가지만 생성자로 전달하면 됨
  - enabled, accountNonExpired, credentialsNonExpired, accountNonLocked 는 자동으로 true로

#### 구현 예시(User 클래스를 상속한 경우)

```java
package io.clroot.club.security.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.User;

import java.util.Collection;

@Slf4j
@Getter
@Setter
@ToString
public class ClubAuthMemberDTO extends User {

    private String email;

    private String name;

    private boolean fromSocial;

    public ClubAuthMemberDTO(String username, String password, boolean fromSocial,
                             Collection<? extends GrantedAuthority> authorities) {
        super(username, password, authorities);

        this.email = username;
        this.fromSocial = fromSocial;
    }
}
```

## UserDetailsService 인터페이스

- 스프링 시큐리티에서 인증을 담당하는 AuthenticationManager는 UserDetailsService를 호출하여 사용자 정보를 가져옴
- UserDetailsService를 구현한 클래스가 Bean으로 등록되면, 스프링 시큐리티에서 UserDetailsService를 인식하여 별도 설정 구성할 필요 ❌

### 메서드

- UserDetails loadUserByUsername(String username)
  - 유저를 찾을 수 없을 경우, UserNameNotFoundException 발생

### 구현체

- CachingUserDetailsService
- InMemoryDaoImpl
- InMemoryUserDetailsManager
- JdbcDaoImpl
- JdbcUserDetailsManager
- LdapUserDetailsManager
- LdapUserDetailsService
- UserDetailsServiceWrapper

### 사용

- 클래스를 생성하여 UserDetailsService를 직접 구현
- loadUserByUsername 메서드를 구현 할 때, user 정보가 persist 된 곳에서 데이터 읽어오기

#### 구현 예시

```java
package io.clroot.club.security.service;

import io.clroot.club.entity.ClubMember;
import io.clroot.club.repository.ClubMemberRepository;
import io.clroot.club.security.dto.ClubAuthMemberDTO;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;
import java.util.stream.Collectors;

@Service
@Transactional(readOnly = true)
@RequiredArgsConstructor
@Slf4j
public class ClubUserDetailsService implements UserDetailsService {

    private final ClubMemberRepository clubMemberRepository;

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        log.info("ClubUserDetailsService loadUserByUsername " + username);

        Optional<ClubMember> result = clubMemberRepository.findByEmail(username, false);

        if (result.isEmpty()) {
            throw new UsernameNotFoundException("Check Email or Social");
        }

        ClubMember clubMember = result.get();

        ClubAuthMemberDTO clubAuthMember = new ClubAuthMemberDTO(
                clubMember.getEmail(),
                clubMember.getPassword(),
                clubMember.isFromSocial(),
                clubMember.getRoleSet().stream().map(
                        role -> new SimpleGrantedAuthority("ROLE_" + role.name())
                ).collect(Collectors.toSet())
        );

        clubAuthMember.setName(clubAuthMember.getName());
        clubAuthMember.setFromSocial(clubAuthMember.isFromSocial());

        return clubAuthMember;
    }
}
```
