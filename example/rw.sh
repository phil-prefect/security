#!/bin/sh

killall envset_proc
sleep 1
rm -f instance/question1/server/aspect_policy.cfg

yes|cp instance/question1/server/plugin_config.cfg.access instance/question1/server/plugin_config.cfg
yes|cp instance/question1/server/sys_config.cfg.label instance/question1/server/sys_config.cfg
yes|cp instance/question1/server/router_policy.cfg.record instance/question1/server/router_policy.cfg
yes|cp instance/question1/server/aspect_policy.cfg.access instance/question1/server/aspect_policy.cfg

rm -f instance/question1/user1/aspect_policy.cfg
rm -f instance/question1/user2/aspect_policy.cfg
rm -f instance/question1/user3/aspect_policy.cfg

yes|cp instance/question1/user1/sys_config.cfg.record instance/question1/user1/sys_config.cfg
yes|cp instance/question1/user1/router_policy.cfg.record instance/question1/user1/router_policy.cfg

yes|cp instance/question1/user2/sys_config.cfg.record instance/question1/user1/sys_config.cfg
yes|cp instance/question1/user2/router_policy.cfg.record instance/question1/user1/router_policy.cfg

yes|cp instance/question1/user3/sys_config.cfg.record instance/question1/user1/sys_config.cfg
yes|cp instance/question1/user3/router_policy.cfg.record instance/question1/user1/router_policy.cfg

sleep 1


sh run_cube.sh exec_def/question1/_login_server.def &
sleep 1
sh run_cube.sh exec_def/question1/_login_user1.def login.msg write.msg read.msg &

sleep 1
sh run_cube.sh exec_def/question1/_login_user2.def login.msg read.msg &

sleep 1
sh run_cube.sh exec_def/question1/_login_user3.def login.msg write.msg read.msg
#sh run_cube.sh exec_def/question2/_file_sender.def base_msg.msg
