# [DirectX9] CrazyArcade 모작
게임 학원에서 C/C++과 DirectX 9을 사용해 3일 동안 제작한 게임입니다. 클라이언트 개발뿐만 아니라, 소켓 프로그래밍 지식을 활용해 간단한 게임 서버를 만들어 멀티 게임으로 구현했습니다.

![crazyArcadeMain](https://github.com/user-attachments/assets/2a1294ec-73d0-478c-98ef-1118c9d90c84)

# 구현 컨텐츠 및 기능
## 1. 클라이언트
Socket Manager를 통해 서버와 통신합니다.

통신량을 최소화하기 위해 캐릭터 이동, 물풍선 설치, 블록 파괴 등 중요한 이벤트 발생 시에만 서버로 패킷을 전송하도록 설계했습니다.

![crazyArcadeBomb](https://github.com/user-attachments/assets/07d7db4d-5d37-4a61-8165-96767c823b2b)

![crazyArcadeDeath](https://github.com/user-attachments/assets/ea2f718c-bd15-4175-945d-c171ce38c072)

## 2. 게임 서버
### 2.1. 클라이언트 접속
클라이언트가 서버에 접속하면 자동으로 게임이 실행됩니다.

Session Manager를 사용해 클라이언트 정보를 세션으로 관리하고, 이를 리스트에 저장해 처리합니다.
![crazyArcadeServer](https://github.com/user-attachments/assets/6f8d4242-1293-407b-92a8-751432bcfc19)

캐릭터가 생성되면, 해당 프로젝트의 프로토콜에 따라 세션(Session)을 생성합니다.

이벤트 발생 시마다 세션을 업데이트합니다. 이후, 리스트에 있는 모든 소켓에 세션의 상태(Status)를 브로드캐스팅으로 전송합니다. 

캐릭터가 사망하면 리스트에서 해당 캐릭터를 제거합니다.

### 2.2. 맵 관리
맵 데이터는 클라이언트가 아닌 서버에서 관리됩니다. 서버가 실행될 때, 맵 파일 데이터를 읽어들여 벡터에 저장해 관리합니다.

따라서, 게임이 갑자기 종료된 후에도 서버가 계속 실행 중이라면, 재접속한 클라이언트는 이전에 플레이하던 맵에서 게임을 그대로 이어서 진행할 수 있습니다.

![crazyArcadeMap](https://github.com/user-attachments/assets/b7c3d972-5e9a-4a1e-ab4f-c604095c3ca2)
