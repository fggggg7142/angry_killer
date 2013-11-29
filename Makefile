#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.0.0\"
INCPATH=-I./ \
  -I../ \
  -I./libs/glog/include \
  -I./ \
  -I../ \
  -I./libs/bhook/include
DEP_INCPATH=-I../../../../public/sofa-pbrpc \
  -I../../../../public/sofa-pbrpc/include \
  -I../../../../public/sofa-pbrpc/output \
  -I../../../../public/sofa-pbrpc/output/include \
  -I../../../../thirdsrc/gflags \
  -I../../../../thirdsrc/gflags/include \
  -I../../../../thirdsrc/gflags/output \
  -I../../../../thirdsrc/gflags/output/include \
  -I../../../../thirdsrc/protobuf \
  -I../../../../thirdsrc/protobuf/include \
  -I../../../../thirdsrc/protobuf/output \
  -I../../../../thirdsrc/protobuf/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=411ae0f4aeb7d6595b018b3c38f8ee4d  COMAKE


.PHONY:all
all:comake2_makefile_check libangry_killer.a libakhook.so angry_killer output_bin 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf libangry_killer.a
	rm -rf ./output/lib/libangry_killer.a
	rm -rf ./output/include/perform_show.h
	rm -rf ./output/include/perform_helper.h
	rm -rf ./output/include/fd_control.h
	rm -rf ./output/include/common.h
	rm -rf ./output/include/cpu_control.h
	rm -rf ./output/include/mem_control.h
	rm -rf ./output/include/control_manager.h
	rm -rf ./output/include/processor_control.h
	rm -rf ./output/include/net_control.h
	rm -rf ./output/include/net_server.h
	rm -rf ./output/include/disk_write.h
	rm -rf ./output/include/pid_control.h
	rm -rf ./output/include/port_control.h
	rm -rf ./output/include/hook_helper.h
	rm -rf libakhook.so
	rm -rf ./output/lib/libakhook.so
	rm -rf angry_killer
	rm -rf ./output/bin/angry_killer
	rm -rf output_bin
	rm -fr output/bin/hook output/bin/libakhook.so
	rm -rf angry_killer_perform_show.o
	rm -rf angry_killer_perform_helper.o
	rm -rf angry_killer_fd_control.o
	rm -rf angry_killer_common.o
	rm -rf angry_killer_cpu_control.o
	rm -rf angry_killer_mem_control.o
	rm -rf angry_killer_control_manager.o
	rm -rf angry_killer_processor_control.o
	rm -rf net/net_tools.pb.cc
	rm -rf net/net_tools.pb.h
	rm -rf net/angry_killer_net_tools.pb.o
	rm -rf net/angry_killer_net_control.o
	rm -rf net/angry_killer_net_server.o
	rm -rf disk/angry_killer_disk_write.o
	rm -rf process/angry_killer_pid_control.o
	rm -rf net/angry_killer_port_control.o
	rm -rf hook/angry_killer_hook_helper.o
	rm -rf angry_killer_ak_flags.o
	rm -rf hook/akhook_htest2.o
	rm -rf hook/akhook_hook_helper.o
	rm -rf akhook_ak_flags.o
	rm -rf angry_killer_angry_killer.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

libangry_killer.a:angry_killer_perform_show.o \
  angry_killer_perform_helper.o \
  angry_killer_fd_control.o \
  angry_killer_common.o \
  angry_killer_cpu_control.o \
  angry_killer_mem_control.o \
  angry_killer_control_manager.o \
  angry_killer_processor_control.o \
  net/angry_killer_net_tools.pb.o \
  net/angry_killer_net_control.o \
  net/angry_killer_net_server.o \
  disk/angry_killer_disk_write.o \
  process/angry_killer_pid_control.o \
  net/angry_killer_port_control.o \
  hook/angry_killer_hook_helper.o \
  angry_killer_ak_flags.o \
  perform_show.h \
  perform_helper.h \
  fd_control.h \
  common.h \
  cpu_control.h \
  mem_control.h \
  control_manager.h \
  processor_control.h \
  net/net_control.h \
  net/net_server.h \
  disk/disk_write.h \
  process/pid_control.h \
  net/port_control.h \
  hook/hook_helper.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibangry_killer.a[0m']"
	ar crs libangry_killer.a angry_killer_perform_show.o \
  angry_killer_perform_helper.o \
  angry_killer_fd_control.o \
  angry_killer_common.o \
  angry_killer_cpu_control.o \
  angry_killer_mem_control.o \
  angry_killer_control_manager.o \
  angry_killer_processor_control.o \
  net/angry_killer_net_tools.pb.o \
  net/angry_killer_net_control.o \
  net/angry_killer_net_server.o \
  disk/angry_killer_disk_write.o \
  process/angry_killer_pid_control.o \
  net/angry_killer_port_control.o \
  hook/angry_killer_hook_helper.o \
  angry_killer_ak_flags.o
	mkdir -p ./output/lib
	cp -f --link libangry_killer.a ./output/lib
	mkdir -p ./output/include
	cp -f --link perform_show.h perform_helper.h fd_control.h common.h cpu_control.h mem_control.h control_manager.h processor_control.h net/net_control.h net/net_server.h disk/disk_write.h process/pid_control.h net/port_control.h hook/hook_helper.h ./output/include

libakhook.so:hook/akhook_htest2.o \
  hook/akhook_hook_helper.o \
  akhook_ak_flags.o \
  ./libs/bhook/lib/libbhook.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibakhook.so[0m']"
	$(CXX) -shared hook/akhook_htest2.o \
  hook/akhook_hook_helper.o \
  akhook_ak_flags.o -Xlinker "-(" ./libs/bhook/lib/libbhook.a ../../../../public/sofa-pbrpc/lib/libsofa_pbrpc.a \
  ../../../../public/sofa-pbrpc/lib/libtcmalloc_minimal.a \
  ../../../../thirdsrc/gflags/output/lib/libgflags.a \
  ../../../../thirdsrc/gflags/output/lib/libgflags_nothreads.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotobuf-lite.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotobuf.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotoc.a -lpthread \
  -lz \
  -ldl \
  -fPIC -Xlinker "-)" -o libakhook.so
	mkdir -p ./output/lib
	cp -f --link libakhook.so ./output/lib

angry_killer:angry_killer_angry_killer.o \
  ./output/lib/libangry_killer.a \
  ./libs/glog/lib/libglog.a \
  ./libs/bhook/lib/libbhook.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer[0m']"
	$(CXX) angry_killer_angry_killer.o -Xlinker "-(" ./output/lib/libangry_killer.a \
  ./libs/glog/lib/libglog.a \
  ./libs/bhook/lib/libbhook.a ../../../../public/sofa-pbrpc/lib/libsofa_pbrpc.a \
  ../../../../public/sofa-pbrpc/lib/libtcmalloc_minimal.a \
  ../../../../thirdsrc/gflags/output/lib/libgflags.a \
  ../../../../thirdsrc/gflags/output/lib/libgflags_nothreads.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotobuf-lite.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotobuf.a \
  ../../../../thirdsrc/protobuf/output/lib/libprotoc.a -lpthread \
  -lz \
  -ldl \
  -fPIC -Xlinker "-)" -o angry_killer
	mkdir -p ./output/bin
	cp -f --link angry_killer ./output/bin

output_bin:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40moutput_bin[0m']"
	mkdir -p output/bin/
	cp -r libs/bhook/scripts/bhook output/bin/akhook
	cp -r libakhook.so output/bin/

angry_killer_perform_show.o:perform_show.cpp \
  perform_show.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  common.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_perform_show.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_perform_show.o perform_show.cpp

angry_killer_perform_helper.o:perform_helper.cpp \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_perform_helper.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_perform_helper.o perform_helper.cpp

angry_killer_fd_control.o:fd_control.cpp \
  fd_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  disk/disk_write.h \
  common.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_fd_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_fd_control.o fd_control.cpp

angry_killer_common.o:common.cpp \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_common.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_common.o common.cpp

angry_killer_cpu_control.o:cpu_control.cpp \
  cpu_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_cpu_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_cpu_control.o cpu_control.cpp

angry_killer_mem_control.o:mem_control.cpp \
  mem_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_mem_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_mem_control.o mem_control.cpp

angry_killer_control_manager.o:control_manager.cpp \
  control_manager.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  mem_control.h \
  cpu_control.h \
  net/net_control.h \
  common.h \
  net/net_tools.pb.h \
  net/net_server.h \
  net/port_control.h \
  net/net_control.h \
  net/net_server.h \
  processor_control.h \
  fd_control.h \
  disk/disk_write.h \
  common.h \
  process/pid_control.h \
  common.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_control_manager.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_control_manager.o control_manager.cpp

angry_killer_processor_control.o:processor_control.cpp \
  processor_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_processor_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_processor_control.o processor_control.cpp

net/net_tools.pb.cc \
  net/net_tools.pb.h:net/net_tools.proto
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/net_tools.pb.cc \
  net/net_tools.pb.h[0m']"
	../../../..//thirdsrc/protobuf/install/bin/protoc --cpp_out=net --proto_path=net  net/net_tools.proto

net/net_tools.proto:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/net_tools.proto[0m']"
	@echo "ALREADY BUILT"

net/angry_killer_net_tools.pb.o:net/net_tools.pb.cc \
  net/net_tools.pb.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/angry_killer_net_tools.pb.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o net/angry_killer_net_tools.pb.o net/net_tools.pb.cc

net/angry_killer_net_control.o:net/net_control.cpp \
  net/net_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  net/net_tools.pb.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/angry_killer_net_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o net/angry_killer_net_control.o net/net_control.cpp

net/angry_killer_net_server.o:net/net_server.cpp \
  net/net_server.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  net/net_tools.pb.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/angry_killer_net_server.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o net/angry_killer_net_server.o net/net_server.cpp

disk/angry_killer_disk_write.o:disk/disk_write.cpp \
  disk/disk_write.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdisk/angry_killer_disk_write.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o disk/angry_killer_disk_write.o disk/disk_write.cpp

process/angry_killer_pid_control.o:process/pid_control.cpp \
  process/pid_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mprocess/angry_killer_pid_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o process/angry_killer_pid_control.o process/pid_control.cpp

net/angry_killer_port_control.o:net/port_control.cpp \
  net/port_control.h \
  net/net_control.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  net/net_tools.pb.h \
  net/net_server.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mnet/angry_killer_port_control.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o net/angry_killer_port_control.o net/port_control.cpp

hook/angry_killer_hook_helper.o:hook/hook_helper.cpp \
  hook/hook_helper.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mhook/angry_killer_hook_helper.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o hook/angry_killer_hook_helper.o hook/hook_helper.cpp

angry_killer_ak_flags.o:ak_flags.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_ak_flags.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_ak_flags.o ak_flags.cpp

hook/akhook_htest2.o:hook/htest2.cpp \
  libs/bhook/include/bhook.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  hook/hook_helper.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mhook/akhook_htest2.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o hook/akhook_htest2.o hook/htest2.cpp

hook/akhook_hook_helper.o:hook/hook_helper.cpp \
  hook/hook_helper.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mhook/akhook_hook_helper.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o hook/akhook_hook_helper.o hook/hook_helper.cpp

akhook_ak_flags.o:ak_flags.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40makhook_ak_flags.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o akhook_ak_flags.o ak_flags.cpp

angry_killer_angry_killer.o:angry_killer.cpp \
  control_manager.h \
  common.h \
  perform_helper.h \
  libs/glog/include/glog/logging.h \
  libs/glog/include/glog/log_severity.h \
  libs/glog/include/glog/vlog_is_on.h \
  mem_control.h \
  cpu_control.h \
  net/net_control.h \
  common.h \
  net/net_tools.pb.h \
  net/net_server.h \
  net/port_control.h \
  net/net_control.h \
  net/net_server.h \
  processor_control.h \
  fd_control.h \
  disk/disk_write.h \
  common.h \
  process/pid_control.h \
  common.h \
  perform_show.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mangry_killer_angry_killer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o angry_killer_angry_killer.o angry_killer.cpp

endif #ifeq ($(shell uname -m),x86_64)


