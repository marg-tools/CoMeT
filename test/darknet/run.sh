#!/bin/bash
for (( c=1; c<=4; c++ ))
do
        mknod alexnet_${c}_pipe.sift p

	# Uncomment appropriate DNN -- AlexNet, ResNet 18/34/50, VGG-16, RNN-3, and YOLOv3-Tiny.

	#mknod resnet18_${c}_pipe.sift p
	#mknod resnet34_${c}_pipe.sift p
	#mknod resnet50_${c}_pipe.sift p
	#mknod vgg-16_${c}_pipe.sift p
	#mknod yolov3-tiny_${c}_pipe.sift p
	#mknod rnn_${c}_pipe.sift p
done

for (( c=1; c<=4; c++ ))
do
        ../../record-trace -o alexnet_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/alexnet.cfg alexnet.weights data/dog.jpg -p1 &
	
	# Uncomment appropriate DNN -- AlexNet, ResNet 18/34/50, VGG-16, RNN-3, and YOLOv3-Tiny.

	#../../record-trace -o resnet18_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/resnet18.cfg resnet18.weights data/dog.jpg -p1 &
	#../../record-trace -o resnet34_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/resnet34.cfg resnet34.weights data/dog.jpg -p1 &
	#../../record-trace -o resnet50_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/resnet50.cfg resnet50.weights data/dog.jpg -p1 &
	#../../record-trace -o vgg-16_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/vgg-16.cfg vgg-16.weights data/dog.jpg -p1 &
	#../../record-trace -o yolov3-tiny_${c}_pipe -- ./darknet classifier predict cfg/imagenet1k.data cfg/yolov3-tiny.cfg yolov3-tiny.weights data/dog.jpg -p1 &
	#../../record-trace -o rnn_${c}_pipe --roi -- ./darknet rnn generate cfg/rnn.cfg grrm.weights -srand 0 -seed JON -p1 &
done

../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=alexnet_1_pipe.sift,alexnet_2_pipe.sift,alexnet_3_pipe.sift,alexnet_4_pipe.sift 

# Uncomment appropriate DNN -- AlexNet, ResNet 18/34/50, VGG-16, RNN-3, and YOLOv3-Tiny.

#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=resnet18_1_pipe.sift,resnet18_2_pipe.sift,resnet18_3_pipe.sift,resnet18_4_pipe.sift
#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=resnet34_1_pipe.sift,resnet34_2_pipe.sift,resnet34_3_pipe.sift,resnet34_4_pipe.sift
#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=resnet50_1_pipe.sift,resnet50_2_pipe.sift,resnet50_3_pipe.sift,resnet50_4_pipe.sift
#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=vgg-16_1_pipe.sift,vgg-16_2_pipe.sift,vgg-16_3_pipe.sift,vgg-16_4_pipe.sift
#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=yolov3-tiny_1_pipe.sift,yolov3-tiny_2_pipe.sift,yolov3-tiny_3_pipe.sift,yolov3-tiny_4_pipe.sift
#../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=rnn_1_pipe.sift,rnn_2_pipe.sift,rnn_3_pipe.sift,rnn_4_pipe.sift


