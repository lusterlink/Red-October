#ifndef GRIPPER_H_
#define GRIPPER_H_

/**
 * @file gripper.hpp
 * @author
 * @version 1.0
 *
 * @section DESCRIPTION
 * Welcome to the gripper class.  This class shall define the methods
 * to directly interface with the COM port to control the gripper.
 * At this level, the only actions able to be performed are low level.
 *
 * @section LICENSE
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

class Gripper {
public:
    /**
     * Get the current status of the gripper.
     *
     * This method gets the current status of the gripper.  This is
     * a blocking function that returns the status the gripper in the
     * pass in pointer and the error code if applicable in its
     * return.
     *
     * @param int *status: Pointer to the integer to place status.
     * @return Resulting error code.
     */
    int get_gripper_status(int *status);

    /**
     * Set the current status of the gripper.
     *
     * This method sets the current status of the griper.  This is
     * a non-blocking function that changes the internal status
     * of the gripper state and sends the command to the actual
     * hardware.
     *
     * @param int status: The desired gripper status
     * @return Resulting error code.
     */
    int set_gripper_satus(int status);
private:

};

#endif
