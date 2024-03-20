#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "libflex.h"

int main() {
	uint8_t buff[FLX_PKT_MAXIMUM_SIZE] = {
		FLX_ACT_NOTIFY,
		FLX_WATCH_REM,
		0x0C,
		'h',
		'e',
		'l',
		'l',
		'o',
		'\0',
		'h',
		'e',
		'l',
		'l',
		'o',
		'\0',
	};

	char *lol = "hey there whats up";
	char *jej = "whatcha doin son";

	char *testData[2] = {
		lol,
		jej
	};

	uint8_t cereal[1024] = {0};

	struct serialize_result* result = (struct serialize_result*)malloc(sizeof(struct serialize_result));
	serialize_result_factory(result);

	struct flex_msg *message = (struct flex_msg*)malloc(sizeof(struct flex_msg));
	flex_msg_factory(message);

	flx_option replyType = FLX_REPLY_UNSET;

	deserialize(buff, message, result);

	if (result->reply != FLX_REPLY_VALID) {
		fprintf(stderr, "GOT %d\n", result->reply);
		//return 1;
	}

	print_packet(message);
	serialize(cereal, message, result);

	for (int i = 0; i < 3 + cereal[3]; i++) {
		printf("%x ", cereal[i]);
	}
	printf("\n");

	message->data = testData;
	message->dataLen = 2;

	serialize(cereal, message, result);
	if (result->reply != FLX_REPLY_VALID) {
		fprintf(stderr, "GOT %d\n", result->reply);
		return 1;
	}

	for (int i = 0; i < 3 + cereal[3]; i++) {
		printf("%x ", cereal[i]);
	}
	printf("\n");

	return 0;
}
