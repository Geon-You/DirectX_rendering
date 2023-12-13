## DirectX 9을 사용하였다
## 기존의 윈도우 핸들러를 가져와 hdc에 렌더링하는 방식에서 DirectX를 사용하여 장치를 조사하고 지원하는 버텍스 프로세싱에 따라 나눠 스왑체인 방식으로 버퍼에 렌더링한다.
## 텍스처를 읽어와서 싱글 텍스처와 멀티 텍스처로 나눠 사용한다. 싱글 텍스처는 Background 등에 사용되는 텍스처이고 멀티 텍스처는 캐릭터의 Motion, Effect 등등 여러 프레임으로 이루어진 텍스차로 구분하였다.
## 텍스처의 타입에 따라 렌더링하는 방식이 달라진다.
## Prototype 디자인 패턴을 사용하여 Scene에서 사용되는 모든 객체는 원형 객체를 복제하여 생성하도록 하였다.
