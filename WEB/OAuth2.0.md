# OAuth2.0

- 공개 API(Open API)로 제공되는 표준 인증 방법

## Flow

```
    +--------+                               +---------------+
    |        |--(A)- Authorization Request ->|   Resource    |
    |        |                               |     Owner     |
    |        |<-(B)-- Authorization Grant ---|               |
    |        |                               +---------------+
    |        |
    |        |                               +---------------+
    |        |--(C)-- Authorization Grant -->| Authorization |
    | Client |                               |     Server    |
    |        |<-(D)----- Access Token -------|               |
    |        |                               +---------------+
    |        |
    |        |                               +---------------+
    |        |--(E)----- Access Token ------>|    Resource   |
    |        |                               |     Server    |
    |        |<-(F)--- Protected Resource ---|               |
    +--------+                               +---------------+
```

- Resource Owner: 정보의 소유권을 가진 소유자(= User)
- Authorization Server: User를 인증하는 서버, 클라이언트에게 Access Token을 발급
- Resource Server: User의 정보를 가지고 있는 Google, Kakao와 같은 OAuth 서비스 제공자
- Client: OAuth를 사용하여 서비스 제공자로부터 사용자의 정보를 요청하는 곳 -> 개발하는 서비스가 Client 입장

### 설명

- Client가 User에게 인증 정보를 요청
- 클라이언트가 User로 부터 받은 인증 정보를 사용하여, OAuth 서비스 제공자에게 액세스 토큰(= Access Token, Request Token) 발급 요청
  - User로 부터 전달받은 인증 정보가 유효할 경우, 유저의 데이터에 접근할 액세스 토큰 발급
- 클라이언트가 발급 받은 액세스 토큰을 이용하여, OAuth 서비스 제공자에게 User의 정보 요청
  - OAuth 서비스 제공자가 User의 정보 제공
- 클라이언트가 받은 유저 정보를 토대로 로그인 or 회원가입 절차 진행
