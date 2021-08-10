# AuthenticationSuccessHandler 인터페이스

- 인증이 성공하거나 실패한 후, 처리를 지정할 때 사용
- 일반적으로는 리다이렉션이나 포워딩을 사용하여, 후속 목적지로 전달
- 필요시 다른 로직 포함

## 메서드

- default void onAuthenticationSuccess​(HttpServletRequest request, HttpServletResponse response, FilterChain chain, Authentication authentication)
  - IOException, ServletException 발생 가능
- void onAuthenticationSuccess​(HttpServletRequest request, HttpServletResponse response, Authentication authentication)
  - IOException, ServletException 발생 가능

## 구현체

- ForwardAuthenticationSuccessHandler
- SavedRequestAwareAuthenticationSuccessHandler
- SimpleUrlAuthenticationSuccessHandler

## 구현 예시

```java
// ClubLoginSuccessHandler.java
package io.clroot.club.security.handler;

import io.clroot.club.security.dto.ClubAuthMemberDTO;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.core.Authentication;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.DefaultRedirectStrategy;
import org.springframework.security.web.RedirectStrategy;
import org.springframework.security.web.authentication.AuthenticationSuccessHandler;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Slf4j
@RequiredArgsConstructor
public class ClubLoginSuccessHandler implements AuthenticationSuccessHandler {

    private final RedirectStrategy redirectStrategy = new DefaultRedirectStrategy();

    private final PasswordEncoder passwordEncoder;

    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response,
                                        Authentication authentication) throws IOException, ServletException {
        log.info("------------------------------");
        log.info("onAuthenticationSuccess ");

        ClubAuthMemberDTO authMember = (ClubAuthMemberDTO) authentication.getPrincipal();

        boolean fromSocial = authMember.isFromSocial();
        boolean passwordResult = passwordEncoder.matches("1111", authMember.getPassword());

        log.info("Need Modify Member?" + (fromSocial && passwordResult));

        if (fromSocial && passwordResult) {
            redirectStrategy.sendRedirect(request, response, "/member/modify?from=social");
        }
    }
}

```

```java
// SecurityConfig.java
package io.clroot.club.config;

import io.clroot.club.security.handler.ClubLoginSuccessHandler;
import lombok.extern.slf4j.Slf4j;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;

@Configuration
@Slf4j
public class SecurityConfig extends WebSecurityConfigurerAdapter {

    @Bean
    PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    ClubLoginSuccessHandler successHandler() {
        return new ClubLoginSuccessHandler(passwordEncoder());
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()
                .antMatchers("/sample/all").permitAll()
                .antMatchers("/sample/member").hasRole("USER");
        http.formLogin();
        http.csrf().disable();
        http.logout();

        http.oauth2Login().successHandler(successHandler());
    }
}

```

- ClubLoginSuccessHandler Bean 등록
- HttpSecurity 구성에서 oauth2Login() 성공시 successHandler 등록
