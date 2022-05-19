# 과제#2 - 다층신경망 학습 최적화하기
------------------------------------
* 강의명 : 딥러닝_02
* 담당 교수 : 김태형
* 학번 : 20190850
* 이름 : 이수진

## 설계내용
------------------------------------
1. Dataset
* cifar-10 사용
* input_size : 3072
* output_size : 10

2. 학습 코드 구조화 : directory 및 files 구조
* ```config/```
    * ```config.yaml``` : 설정 파일

* ```data/``` : 데이터(cifar-10) 파일

* ```nets/``` : 인공신경망 및 계층 파일
    * ```data_loader.py``` : ```def load_cifar10(path)```
    *  ```layers.py``` : activate function, Bacth Normalization, Dropout
    * ```multi_layer_net.py``` : ```Class multi_layer_net```

* ```utils/``` : 최적화 함수, 학습 관련 함수 및 기타 함수 등
    * ```logger.py``` : 로그 기록 class Logger
    * ```utils.py``` : 학습 관련 함수 및 기타 함수
    *  ```optimizer.py``` : optimizer
    * ```trainer.py``` : ```class Trainer```

* ```results/``` : train 및 test 결과 파일 저장
    * ```train.log``` : train 결과 log
    * ```test.log``` : test 결과 log
    * ```train-val-result.png``` : 학습 결과 성능 그래프

* ```weights/``` : 가중치 파일
    * ```temp.npy``` : 가중치 파일

* ```train.py``` : 학습 알고리즘 코드 파일
* ```evalute.py``` : 데이터셋으로 모델을 시험하는 코드 파일
* ```README.md``` : 과제 보고서


## 최적화 방법
------------------------------------
* ```config/config.yaml``` 참고
1. epochs : 30
2. learning_rate : 0.001
3. weight_decay : 0.00001
4. hidden_size : [100, 100]
5. weight_init_std : 0.01
6. use_batchnorm : True
7. use_dropout : True
8. batch_size : 100
9. optimizer : adam
10. activate function : relu
11. weight_init : he init


## Usage
------------------------------------
1. 학습 : ```python train.py```
2. 평가 : ```python evaluate.py```


## Result
------------------------------------
* ```train.log``` 및 ```test.log``` 참고
1. train_acc : 0.59745
> 대체적으로 57 ~ 60%의 성능을 보임
2. val_acc : 0.4906
> 대체적으로 48 ~ 50%의 성능을 보임
3. test_acc : 0.3153
> 대체적으로 28 ~ 32%의 성능을 보임