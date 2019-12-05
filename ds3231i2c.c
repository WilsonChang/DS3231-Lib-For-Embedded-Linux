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


#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include "ds3231i2c.h"

int fd = 0;
struct DS3231data dsdata;

const char * weekdayname[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
};


void bcd2str(char * str, int d)
{
    int dd;
    dd = d >> 4;
    str[0] = '0' + dd;
//printf("%x, %c, \n", dd, str[0]);
    dd = d & 0x0f;
    str[1] = '0' + dd;
    str[2] = 0;
//printf("%x,%x, %s\n",d,dd,str);
}


int ds3231init(const char * devname, int i2caddr)
{
    fd = open(devname, O_RDWR);
    if (fd == -1) { 
        printf("open i2c failed\n");
        return -1;
    } else 
        printf("open i2c ok\n");

    int ret = ioctl(fd, I2C_SLAVE, i2caddr);
    if (ret == -1) {
        printf("ioctl i2c failed\n");
        close(fd);
        return -1; }
    else 
        printf("ioctl i2c ok\n");

    return 0;
}

int ds3231close(void) {close(fd);}

int readbyte(int regaddr) 
{
    int data;
   
    write(fd, &regaddr, 1);
    read(fd, &data, 1);
    return data;
}

int dsreadsecond() {return readbyte(0);}
int dsreadminute() {return readbyte(1);}
int dsreadhour() {return readbyte(2);}
int dsreadweek() {return readbyte(3);}
int dsreadday() {return readbyte(4);}
int dsreadmonth() {return readbyte(5);}
int dsreadyear() {return readbyte(6);}


DS3231data * ds3231readall(void) 
{
	
	dsdata.bcdsecond = dsreadsecond();
	bcd2str(dsdata.strsecond, dsdata.bcdsecond);
	dsdata.bcdminute = dsreadminute();
	bcd2str(dsdata.strminute, dsdata.bcdminute);
	dsdata.bcdhour = dsreadhour();
	bcd2str(dsdata.strhour, dsdata.bcdhour);

	dsdata.bcdday = dsreadday();
	bcd2str(dsdata.strday, dsdata.bcdday);
	dsdata.bcdmonth = dsreadmonth();
	bcd2str(dsdata.strmonth, dsdata.bcdmonth);
	dsdata.bcdyear = dsreadyear();
	bcd2str(dsdata.stryear, dsdata.bcdyear);


	dsdata.bcdweekday = dsreadweek();
	strcpy(dsdata.strweekday, weekdayname[dsdata.bcdweekday]);

	//printf("week:%s, %d, year:%s, %d\n", dsdata.strweekday,
	//	dsdata.bcdweekday, dsdata.stryear, dsdata.bcdyear);

        
	return &dsdata;
}







