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
