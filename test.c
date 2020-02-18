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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ds3231i2c.h"


//-------------------------------------------------------------------------

int main(void)
{

	DS3231data * d;
	char s[20];

	ds3231init("/dev/i2c-1", 0x68);
        d = ds3231readall();

        printf("date: 20%s-%s-%s\n", d->stryear, d->strmonth, d->strday);
        printf("time: %s:%s:%s\n", d->strhour, d->strminute,d->strsecond);
        printf("weekday: %s\n", d->strweekday);
 
	ds3231close();
	return 0;
}

