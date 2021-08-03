# 시큐리티를 위한 UserDetailsService

- 스프링 시큐리티에서는 회원, 계정에 대해서 User라는 용어 사용
- 회원을 식별하는 id는 username
- username과 password를 동시에 처리 ❌
  - User의 존재를 확인 한 후
  - password를 검증, 실패시 "bad credentials"
- username과 password 검증 마친 후, URL에 접근할 권한이 있는지 확인 & 인가 진행

## UserDetails 인터페이스

### 메소드

- getAuthorities()
- getPassword()
- getUsername()
- isAccountNonExpired()
- isAccountNonLocked()
- isCredentialsNonExpired()
- isEnabled()

### 구현체

- InetOrgPerson
- LdapUserDetailsImpl
- Person
- User

- UserDetails 인터페이스를 직접 구현하기 보다는, 이미 구현된 User 클래스 등을 상속하여 구현하는 것이 더 수월
- User 클래스의 경우, username, password, (Collection<? extends GrantedAuthority>) authorities 이 세가지만 생성자로 전달하면 됨
  - enabled, accountNonExpired, credentialsNonExpired, accountNonLocked 는 자동으로 true로
