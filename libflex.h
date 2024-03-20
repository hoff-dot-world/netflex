/*  libflex.h - netflex protocol implementation base definitions
    Copyright (C) 2024 mdhoff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include <stdint.h>

typedef uint8_t flx_act;
typedef uint8_t flx_option;

#define FLX_ACT_WATCH					0x00
#define FLX_ACT_QUIT					0x01
#define FLX_ACT_NOTIFY					0x02
#define FLX_ACT_REPLY					0x03
#define FLX_ACT_STATUS					0x04
#define FLX_ACT_UNSET					0xFF

#define FLX_WATCH_ADD					0x00
#define FLX_WATCH_REM					0x01

#define FLX_QUIT_USER					0x00
#define FLX_QUIT_ERROR					0x01

#define FLX_NOTIFY_CREATE				0x00
#define FLX_NOTIFY_DELETE				0x01
#define FLX_NOTIFY_ACCESS				0x02
#define FLX_NOTIFY_CLOSE				0x03
#define FLX_NOTIFY_MODIFY				0x04
#define FLX_NOTIFY_MOVE					0x05

#define FLX_REPLY_VALID					0x00
#define FLX_REPLY_BAD_SIZE	 			0x01
#define FLX_REPLY_BAD_ACTION			0x02
#define FLX_REPLY_BAD_OPTION			0x03
#define FLX_REPLY_BAD_PATH 				0x04
#define FLX_REPLY_INVALID_DATA			0x05
#define FLX_REPLY_UNSET					0xFF

#define FLX_STATUS_SUCCESS				0x00
#define FLX_STATUS_ERR_INIT_INOTIFY 	0x01
#define FLX_STATUS_ERR_ADD_WATCH 		0x02
#define FLX_STATUS_ERR_READ_INOTIFY 	0x03

#define FLX_UNSET_UNSET					0xFF

#define FLX_PKT_MINIMUM_SIZE			3
#define FLX_PKT_MAXIMUM_SIZE			255

#define FLX_DLEN_WATCH					1
#define FLX_DLEN_QUIT					0
#define FLX_DLEN_NOTIFY					2
#define FLX_DLEN_REPLY					0
#define FLX_DLEN_STATUS					0
#define FLX_DLEN_UNSET					0

struct flex_msg {
	flx_act action;
	flx_option option;
	uint8_t size;

	char **data;
	int dataLen;
};

struct serialize_result {
	int size;
	flx_option reply;
};

void print_packet(struct flex_msg *msg);

void flex_msg_factory(struct flex_msg *message);
void flex_msg_reset(struct flex_msg *message);
void serialize_result_factory(struct serialize_result *result);

void deserialize(uint8_t buffer[FLX_PKT_MAXIMUM_SIZE],
	struct flex_msg *msg, struct serialize_result *result);
void serialize(uint8_t buffer[FLX_PKT_MAXIMUM_SIZE],
	struct flex_msg *msg, struct serialize_result *result);
