/*
 * C codes for DS3231 I2c real clock module
 * read DS3231 data using Linux device file: /dev/i2c-x
 * you need root rights to open device file.
 *
 * This software is free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DS3231I2C
#define __DS3231I2C

typedef struct DS3231data {

int bcdsecond;
char strsecond[3];
int bcdminute;
char strminute[3];
int bcdhour;
char strhour[3];

int bcdday;
char strday[3];
int bcdmonth;
char strmonth[3];
int bcdyear;
char stryear[3];  // no 19, 20...,user add 

int bcdweekday;
char strweekday[16]; //Thursday

} DS3231data;


int ds3231init(const char * devname, int i2caddr);
int ds3231close(void);
DS3231data * ds3231readall(void);


int dsreadsecond();
int dsreadminute();
int dsreadhour();
int dsreadweek();
int dsreadday();
int dsreadmonth();
int dsreadyear();


#endif 


