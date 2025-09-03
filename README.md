### 🗝️ CryptRaider (Unreal Engine 5 · C++)

언리얼 엔진으로 제작한 **동굴 탐험 어드벤처 게임** 프로젝트입니다.  
플레이어는 **오브젝트를 잡아 움직이거나**, **트리거 이벤트**를 통해 새로운 길을 열며 동굴을 탐험합니다.  

#### 🧩 핵심 시스템 (C++ 구현)

- **Grabber (Grabber.cpp)**  
  - `LineTrace`로 플레이어 앞의 상호작용 가능한 오브젝트 감지  
  - `PhysicsHandle`을 이용해 오브젝트를 **잡고 이동** 가능  
  - 입력 이벤트(`Grab`/`Release`)와 연동되어 자연스러운 상호작용 제공  

- **Mover (Mover.cpp)**  
  - 특정 오브젝트(문, 발판 등)의 위치/회전을 업데이트해 **움직이는 구조물** 구현  
  - Tick 함수에서 목표 지점으로 점진적 이동(Lerp) 처리  
  - 트리거나 다른 로직에서 활성화 여부를 제어 가능  

- **TriggerComponent (TriggerComponent.cpp)**  
  - 플레이어 또는 특정 액터가 영역에 들어오면 이벤트 발생  
  - **OnActorBeginOverlap / OnActorEndOverlap**을 활용해 상태 전환  
  - 예: 문 열기, 오브젝트 이동, 새로운 경로 개방  

#### 🎮 게임플레이 흐름
1. 플레이어는 동굴 내부에서 다양한 **상호작용 가능한 오브젝트**를 만남  
2. 오브젝트를 직접 **잡아 옮기거나**, **트리거를 활성화**하여 새로운 길을 엶  


#### 🏗️ 학습/구현 포인트
- 언리얼 **PhysicsHandle**과 `LineTrace`를 이용한 **물체 잡기 시스템**  
- **Trigger Volume** 기반 이벤트 시스템 (Overlap 이벤트)  
- C++ 기반 **오브젝트 이동/회전 로직** 및 모듈화된 컴포넌트 구조

<p align="center">
  <img src="[demo/your_demo.gif](https://github.com/user-attachments/assets/10e164e5-8870-4e04-841a-966cd78917a6)" width="600" alt="게임 데모" />
</p>

