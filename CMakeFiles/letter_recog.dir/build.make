# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Documents/SI4/S2/CV_ML/FaceDetect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Documents/SI4/S2/CV_ML/FaceDetect

# Include any dependencies generated for this target.
include CMakeFiles/letter_recog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/letter_recog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/letter_recog.dir/flags.make

CMakeFiles/letter_recog.dir/letter_recog.cpp.o: CMakeFiles/letter_recog.dir/flags.make
CMakeFiles/letter_recog.dir/letter_recog.cpp.o: letter_recog.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/user/Documents/SI4/S2/CV_ML/FaceDetect/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/letter_recog.dir/letter_recog.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/letter_recog.dir/letter_recog.cpp.o -c /home/user/Documents/SI4/S2/CV_ML/FaceDetect/letter_recog.cpp

CMakeFiles/letter_recog.dir/letter_recog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/letter_recog.dir/letter_recog.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/user/Documents/SI4/S2/CV_ML/FaceDetect/letter_recog.cpp > CMakeFiles/letter_recog.dir/letter_recog.cpp.i

CMakeFiles/letter_recog.dir/letter_recog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/letter_recog.dir/letter_recog.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/user/Documents/SI4/S2/CV_ML/FaceDetect/letter_recog.cpp -o CMakeFiles/letter_recog.dir/letter_recog.cpp.s

CMakeFiles/letter_recog.dir/letter_recog.cpp.o.requires:
.PHONY : CMakeFiles/letter_recog.dir/letter_recog.cpp.o.requires

CMakeFiles/letter_recog.dir/letter_recog.cpp.o.provides: CMakeFiles/letter_recog.dir/letter_recog.cpp.o.requires
	$(MAKE) -f CMakeFiles/letter_recog.dir/build.make CMakeFiles/letter_recog.dir/letter_recog.cpp.o.provides.build
.PHONY : CMakeFiles/letter_recog.dir/letter_recog.cpp.o.provides

CMakeFiles/letter_recog.dir/letter_recog.cpp.o.provides.build: CMakeFiles/letter_recog.dir/letter_recog.cpp.o

# Object files for target letter_recog
letter_recog_OBJECTS = \
"CMakeFiles/letter_recog.dir/letter_recog.cpp.o"

# External object files for target letter_recog
letter_recog_EXTERNAL_OBJECTS =

letter_recog: CMakeFiles/letter_recog.dir/letter_recog.cpp.o
letter_recog: CMakeFiles/letter_recog.dir/build.make
letter_recog: /usr/local/lib/libopencv_xphoto.so.3.1.0
letter_recog: /usr/local/lib/libopencv_xobjdetect.so.3.1.0
letter_recog: /usr/local/lib/libopencv_ximgproc.so.3.1.0
letter_recog: /usr/local/lib/libopencv_xfeatures2d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_tracking.so.3.1.0
letter_recog: /usr/local/lib/libopencv_text.so.3.1.0
letter_recog: /usr/local/lib/libopencv_surface_matching.so.3.1.0
letter_recog: /usr/local/lib/libopencv_structured_light.so.3.1.0
letter_recog: /usr/local/lib/libopencv_stereo.so.3.1.0
letter_recog: /usr/local/lib/libopencv_saliency.so.3.1.0
letter_recog: /usr/local/lib/libopencv_rgbd.so.3.1.0
letter_recog: /usr/local/lib/libopencv_reg.so.3.1.0
letter_recog: /usr/local/lib/libopencv_plot.so.3.1.0
letter_recog: /usr/local/lib/libopencv_optflow.so.3.1.0
letter_recog: /usr/local/lib/libopencv_line_descriptor.so.3.1.0
letter_recog: /usr/local/lib/libopencv_fuzzy.so.3.1.0
letter_recog: /usr/local/lib/libopencv_face.so.3.1.0
letter_recog: /usr/local/lib/libopencv_dpm.so.3.1.0
letter_recog: /usr/local/lib/libopencv_dnn.so.3.1.0
letter_recog: /usr/local/lib/libopencv_datasets.so.3.1.0
letter_recog: /usr/local/lib/libopencv_ccalib.so.3.1.0
letter_recog: /usr/local/lib/libopencv_bioinspired.so.3.1.0
letter_recog: /usr/local/lib/libopencv_bgsegm.so.3.1.0
letter_recog: /usr/local/lib/libopencv_aruco.so.3.1.0
letter_recog: /usr/local/lib/libopencv_videostab.so.3.1.0
letter_recog: /usr/local/lib/libopencv_videoio.so.3.1.0
letter_recog: /usr/local/lib/libopencv_video.so.3.1.0
letter_recog: /usr/local/lib/libopencv_superres.so.3.1.0
letter_recog: /usr/local/lib/libopencv_stitching.so.3.1.0
letter_recog: /usr/local/lib/libopencv_shape.so.3.1.0
letter_recog: /usr/local/lib/libopencv_photo.so.3.1.0
letter_recog: /usr/local/lib/libopencv_objdetect.so.3.1.0
letter_recog: /usr/local/lib/libopencv_ml.so.3.1.0
letter_recog: /usr/local/lib/libopencv_imgproc.so.3.1.0
letter_recog: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
letter_recog: /usr/local/lib/libopencv_highgui.so.3.1.0
letter_recog: /usr/local/lib/libopencv_flann.so.3.1.0
letter_recog: /usr/local/lib/libopencv_features2d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_core.so.3.1.0
letter_recog: /usr/local/lib/libopencv_calib3d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_text.so.3.1.0
letter_recog: /usr/local/lib/libopencv_face.so.3.1.0
letter_recog: /usr/local/lib/libopencv_ximgproc.so.3.1.0
letter_recog: /usr/local/lib/libopencv_xfeatures2d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_shape.so.3.1.0
letter_recog: /usr/local/lib/libopencv_video.so.3.1.0
letter_recog: /usr/local/lib/libopencv_objdetect.so.3.1.0
letter_recog: /usr/local/lib/libopencv_calib3d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_features2d.so.3.1.0
letter_recog: /usr/local/lib/libopencv_ml.so.3.1.0
letter_recog: /usr/local/lib/libopencv_highgui.so.3.1.0
letter_recog: /usr/local/lib/libopencv_videoio.so.3.1.0
letter_recog: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
letter_recog: /usr/local/lib/libopencv_imgproc.so.3.1.0
letter_recog: /usr/local/lib/libopencv_flann.so.3.1.0
letter_recog: /usr/local/lib/libopencv_core.so.3.1.0
letter_recog: CMakeFiles/letter_recog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable letter_recog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/letter_recog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/letter_recog.dir/build: letter_recog
.PHONY : CMakeFiles/letter_recog.dir/build

CMakeFiles/letter_recog.dir/requires: CMakeFiles/letter_recog.dir/letter_recog.cpp.o.requires
.PHONY : CMakeFiles/letter_recog.dir/requires

CMakeFiles/letter_recog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/letter_recog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/letter_recog.dir/clean

CMakeFiles/letter_recog.dir/depend:
	cd /home/user/Documents/SI4/S2/CV_ML/FaceDetect && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Documents/SI4/S2/CV_ML/FaceDetect /home/user/Documents/SI4/S2/CV_ML/FaceDetect /home/user/Documents/SI4/S2/CV_ML/FaceDetect /home/user/Documents/SI4/S2/CV_ML/FaceDetect /home/user/Documents/SI4/S2/CV_ML/FaceDetect/CMakeFiles/letter_recog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/letter_recog.dir/depend

