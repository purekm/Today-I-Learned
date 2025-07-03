Rolling update
여러 인스턴스를 업데이트 하고 싶을 때, 하나씩 업그레이드 하는 방법
이전에는 피드를 여러개 보장해주는 역할로 ReplicaSet을 사용했었는데, Deployment는 Replicaset의 상위 계층으로 Deployment를 생성하면 RS는 자동으로 생성됨

Deployment를 생성시 RS를 자동으로 생성 => RS는 pod를 자동으로 생성
모든 오브젝트를 보고 싶으면 kubctl get all 사용

