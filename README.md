# Letter Classification Neural Network

> 신경회로망을 이용한 자음 문자 이미지 인식 프로그램입니다.

## 개요

2017년도 대학교 연구실에서 진행된 프로젝트이며, 각 자음 이미지를 학습시키고 이를 바탕으로 인식이 가능하도록 구현된 프로젝트입니다. 가볍게 진행된 만큼, 'ㄱ'과 'ㄱ'이 아닌 이미지만을 이용했습니다.

## 기술

- 다층 퍼셉트론

## 학습

학습에 사용된 데이터는 이진 데이터가 아닌 원본 화소값을 이용했으며, 학습 시간은 약 3시간 정도 소요되었습니다.

## 인식

학습된 이미지와 학습을 하지 않은 이미지를 가져와 인식을 진행했을 경우 인식에 성공하는 것을 확인할 수 있었습니다.

![](/docs/result.png)

## 결과

계산량이 많아 학습 시간이 오래 걸린다는 단점을 개선할 필요가 있으며, 은닉층의 수를 적절하게 조절할 필요가 있다는 결과를 도출해냈습니다.