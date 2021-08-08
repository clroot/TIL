# AuthenticationSuccessHandler 인터페이스

- 인증이 성공하거나 실패한 후, 처리를 지정할 때 사용
- 일반적으로는 리다이렉션이나 포워딩을 사용하여, 후속 목적지로 전달
- 필요시 다른 로직 포함

## 메서드

- default void onAuthenticationSuccess​(HttpServletRequest request, HttpServletResponse response, FilterChain chain, Authentication authentication)
- void onAuthenticationSuccess​(HttpServletRequest request, HttpServletResponse response, Authentication authentication)

## 구현체

- ForwardAuthenticationSuccessHandler
- SavedRequestAwareAuthenticationSuccessHandler
- SimpleUrlAuthenticationSuccessHandler
