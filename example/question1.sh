#!/bin/sh

killall envset_proc
sleep 1

sh run_cube.sh exec_def/question1/_login_server.def &
sleep 1
sh run_cube.sh exec_def/question1/_login_user1.def login.msg
#sh run_cube.sh exec_def/question2/_file_sender.def base_msg.msg
