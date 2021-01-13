#undef TRACE_SYSTEM
#define TRACE_SYSTEM	ramhd

#if !defined(_RAMHD_REQ_H) || defined(TRACE_HEADER_MULTI_READ)
#define _RAMHD_REQ_H

#include <linux/tracepoint.h>

TRACE_EVENT(ramhd_req_func,
	/* all the data struct parameter is in form of pointer instead of object */
	TP_PROTO(struct bio *bio, struct bio_vec *bv, char *buffer),

	TP_ARGS(bio, bv, buffer),

	TP_STRUCT__entry(
		__field(sector_t, nr_sector)
		__field(unsigned int, size)
		__field(unsigned int, offset)
		__field(char *, buff)
	),

	TP_fast_assign(
		__entry->nr_sector = bio->bi_iter.bi_sector;
		__entry->size = bv->bv_len;
		__entry->offset = bv->bv_offset;
		__entry->buff = buffer;
	),

	TP_printk("[sector:%8lld] - buffer: 0x%px size = %u@%u", __entry->nr_sector, __entry->buff,
			__entry->size, __entry->offset)
);

#endif /* _RAMHD_REQ_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE ramhd_req

#include <trace/define_trace.h>	
