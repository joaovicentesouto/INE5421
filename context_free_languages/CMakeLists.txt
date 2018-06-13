################################################################################
# This is the main CMakeLists file for the pratical work for INE5421.
#
# Authors: João Vicente Souto e Bruno Izaias Bonotto
#
# Its main goals are:
#   - Set up global variables.
#   - Configure dependencies (find_package).
#   - Add subdirectories.
#
################################################################################

################################################################################
# Project logic 
################################################################################

# Add subdirectories
add_subdirectory(model)
add_subdirectory(tests)

IF(GUI)
    add_subdirectory(gui)
ENDIF(GUI)
