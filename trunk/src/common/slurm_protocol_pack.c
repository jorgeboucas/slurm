#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <src/common/slurm_protocol_pack.h>
#include <src/common/pack.h>
#include <src/common/log.h>
#include <src/slurmctld/slurmctld.h>

void pack_header ( char ** buffer , uint32_t * length , header_t * header )
{
	pack16 ( header -> version , ( void ** ) buffer , length ) ;
	pack16 ( header -> flags , ( void ** ) buffer , length ) ;
	pack16 ( header -> msg_type , ( void ** ) buffer , length ) ;
	pack32 ( header -> body_length , ( void ** ) buffer , length ) ;
}

void unpack_header ( char ** buffer , uint32_t * length , header_t * header )
{
	unpack16 ( & header -> version , ( void ** ) buffer , length ) ;
	unpack16 ( & header -> flags , ( void ** ) buffer , length ) ;
	unpack16 ( & header -> msg_type , ( void ** ) buffer , length ) ;
	unpack32 ( & header -> body_length , ( void ** ) buffer , length ) ;
}

void pack_msg ( char ** buffer , uint32_t * buf_len , slurm_msg_t const * msg )
{
	switch ( msg -> msg_type )
	{
		case REQUEST_NODE_REGISRATION_STATUS :
			break ;
		case MESSAGE_NODE_REGISRATION_STATUS :
			break ;
		case REQUEST_RESOURCE_ALLOCATION :
		case REQUEST_SUBMIT_BATCH_JOB :
			break ;
		case RESPONSE_RESOURCE_ALLOCATION :
			break ;
		case RESPONSE_SUBMIT_BATCH_JOB :
			break ;
		case REQUEST_CANCEL_JOB :
			break ;
		case REQUEST_CANCEL_JOB_STEP :
			break ;
		case REQUEST_SIGNAL_JOB :
			break ;
		case REQUEST_SIGNAL_JOB_STEP :
			break ;
		case REQUEST_RECONFIGURE :
			break ;
		case RESPONSE_CANCEL_JOB :
		case RESPONSE_RECONFIGURE :
		case RESPONSE_CANCEL_JOB_STEP :
		case RESPONSE_SIGNAL_JOB :
		case RESPONSE_SIGNAL_JOB_STEP :
			break ;
		case REQUEST_JOB_INFO :
			break ;
		case REQUEST_JOB_ATTACH :
			break ;
		case RESPONSE_JOB_ATTACH :
			break ;
		case REQUEST_LAUNCH_TASKS :
			break ;
		case REQUEST_GET_JOB_STEP_INFO :
			break ;
		case RESPONSE_GET_JOB_STEP_INFO :
			break ;
		case REQUEST_JOB_RESOURCE :
			break ;
		case RESPONSE_JOB_RESOURCE :
			break ;
		case REQUEST_RUN_JOB_STEP :
			break ;
		case RESPONSE_RUN_JOB_STEP:
			break ;
		case REQUEST_GET_KEY :
			break ;
		case RESPONSE_GET_KEY :
			break ;
		case MESSAGE_TASK_EXIT :
			break ;
		case REQUEST_BATCH_JOB_LAUNCH :
			break ;
		case MESSAGE_UPLOAD_ACCOUNTING_INFO :
			break ;
		default :
			debug ( "No pack method for msg type %i",  msg -> msg_type ) ;
			break;
		
	}
}

void unpack_msg ( char ** buffer , uint32_t * buf_len , slurm_msg_t * msg )
{
	switch ( msg -> msg_type )
	{
		case REQUEST_NODE_REGISRATION_STATUS :
			break ;
		case MESSAGE_NODE_REGISRATION_STATUS :
			break ;
		case REQUEST_RESOURCE_ALLOCATION :
		case REQUEST_SUBMIT_BATCH_JOB :
			break ;
		case RESPONSE_RESOURCE_ALLOCATION :
			break ;
		case RESPONSE_SUBMIT_BATCH_JOB :
			break ;
		case REQUEST_CANCEL_JOB :
			break ;
		case REQUEST_CANCEL_JOB_STEP :
			break ;
		case REQUEST_SIGNAL_JOB :
			break ;
		case REQUEST_SIGNAL_JOB_STEP :
			break ;
		case REQUEST_RECONFIGURE :
			break ;
		case RESPONSE_CANCEL_JOB :
		case RESPONSE_RECONFIGURE :
		case RESPONSE_CANCEL_JOB_STEP :
		case RESPONSE_SIGNAL_JOB :
		case RESPONSE_SIGNAL_JOB_STEP :
			break ;
		case REQUEST_JOB_INFO :
			break ;
		case REQUEST_JOB_ATTACH :
			break ;
		case RESPONSE_JOB_ATTACH :
			break ;
		case REQUEST_LAUNCH_TASKS :
			break ;
		case REQUEST_GET_JOB_STEP_INFO :
			break ;
		case RESPONSE_GET_JOB_STEP_INFO :
			break ;
		case REQUEST_JOB_RESOURCE :
			break ;
		case RESPONSE_JOB_RESOURCE :
			break ;
		case REQUEST_RUN_JOB_STEP :
			break ;
		case RESPONSE_RUN_JOB_STEP:
			break ;
		case REQUEST_GET_KEY :
			break ;
		case RESPONSE_GET_KEY :
			break ;
		case MESSAGE_TASK_EXIT :
			break ;
		case REQUEST_BATCH_JOB_LAUNCH :
			break ;
		case MESSAGE_UPLOAD_ACCOUNTING_INFO :
			break ;
		default :
			debug ( "No pack method for msg type %i",  msg -> msg_type ) ;
			break;
		
	}
}

void pack_node_registration_status_msg ( char ** buffer , uint32_t * length , node_registration_status_msg_t * msg )
{
	pack32 ( msg -> timestamp , ( void ** ) buffer , length ) ;
	pack32 ( msg -> memory_size , ( void ** ) buffer , length ) ;
	pack32 ( msg -> temporary_disk_space , ( void ** ) buffer , length ) ;
}

void unpack_node_registration_status_msg ( char ** buffer , uint32_t * length , node_registration_status_msg_t * msg )
{
	unpack32 ( & msg -> timestamp , ( void ** ) buffer , length ) ;
	unpack32 ( & msg -> memory_size , ( void ** ) buffer , length ) ;
	unpack32 ( & msg -> temporary_disk_space , ( void ** ) buffer , length ) ;
}


int unpack_build_info ( struct build_buffer **build_buffer_ptr, void * buffer , int buffer_size )
{	
	uint16_t uint16_tmp;
	uint32_t uint32_time;
	struct build_table * build_ptr ;
	void * buf_ptr;

	/* alloc memory for structure */	
	build_ptr = malloc ( sizeof ( struct build_table ) ) ;
	if (build_ptr == NULL) 
	{
		return ENOMEM;
	}

	/* load the data values */
	/* unpack timestamp of snapshot */
	buf_ptr = buffer ;
	unpack32 (&uint32_time, &buf_ptr, &buffer_size);

	unpack16 (&build_ptr->backup_interval, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->backup_location, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->backup_machine, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->control_daemon, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->control_machine, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->controller_timeout, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->epilog, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->fast_schedule, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->hash_base, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->heartbeat_interval, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->init_program, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->kill_wait, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->prioritize, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->prolog, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->server_daemon, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack16 (&build_ptr->server_timeout, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->slurm_conf, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&build_ptr->tmp_fs, &uint16_tmp, &buf_ptr, &buffer_size);

	*build_buffer_ptr = malloc (sizeof (struct build_buffer));
	if (*build_buffer_ptr == NULL) {
		free (build_ptr);
		return ENOMEM;
	}
	(*build_buffer_ptr)->last_update = (time_t) uint32_time;
	(*build_buffer_ptr)->raw_buffer_ptr = buffer;
	(*build_buffer_ptr)->build_table_ptr = build_ptr;
	return 0;
}

int pack_job_desc ( job_desc_t *job_desc_ptr, void * buffer , int buf_len )
{	
	void * buf_ptr;
	int buffer_size = buf_len ;
	
	/* load the data values */
	/* unpack timestamp of snapshot */
	buf_ptr = buffer ;

	pack16 (job_desc_ptr->contiguous, &buf_ptr, &buffer_size);
	packstr (job_desc_ptr->features, &buf_ptr, &buffer_size);
	packstr (job_desc_ptr->groups, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->job_id, &buf_ptr, &buffer_size);
	packstr (job_desc_ptr->name, &buf_ptr, &buffer_size);
	packmem (job_desc_ptr->partition_key, 32, &buf_ptr, &buffer_size);
	
	pack32 (job_desc_ptr->min_procs, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->min_memory, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->min_tmp_disk, &buf_ptr, &buffer_size);
	
	packstr (job_desc_ptr->partition, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->priority, &buf_ptr, &buffer_size);
	
	packstr (job_desc_ptr->partition, &buf_ptr, &buffer_size);
	packstr (job_desc_ptr->partition, &buf_ptr, &buffer_size);
	pack16 (job_desc_ptr->shared, &buf_ptr, &buffer_size);

	pack32 (job_desc_ptr->time_limit, &buf_ptr, &buffer_size);
	
	pack32 (job_desc_ptr->num_procs, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->num_nodes, &buf_ptr, &buffer_size);
	pack32 (job_desc_ptr->user_id, &buf_ptr, &buffer_size);

	return buf_len - buffer_size ;
}

int unpack_job_desc ( job_desc_t **job_desc_buffer_ptr, void * buffer , int buffer_size )
{	
	uint16_t uint16_tmp;
	void * buf_ptr;
	job_desc_t * job_desc_ptr ;

	/* alloc memory for structure */
	job_desc_ptr = malloc ( sizeof ( job_desc_t ) ) ;
	if (job_desc_ptr== NULL) 
	{
		return ENOMEM;
	}

	/* load the data values */
	/* unpack timestamp of snapshot */
	buf_ptr = buffer ;

	unpack16 (&job_desc_ptr->contiguous, &buf_ptr, &buffer_size);
	unpackstr_ptr (&job_desc_ptr->features, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&job_desc_ptr->groups, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->job_id, &buf_ptr, &buffer_size);
	unpackstr_ptr (&job_desc_ptr->name, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackmem_ptr ( ( char ** ) &job_desc_ptr->partition_key, &uint16_tmp, &buf_ptr, &buffer_size);
	
	unpack32 (&job_desc_ptr->min_procs, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->min_memory, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->min_tmp_disk, &buf_ptr, &buffer_size);
	
	unpackstr_ptr (&job_desc_ptr->partition, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->priority, &buf_ptr, &buffer_size);
	
	unpackstr_ptr (&job_desc_ptr->partition, &uint16_tmp, &buf_ptr, &buffer_size);
	unpackstr_ptr (&job_desc_ptr->partition, &uint16_tmp, &buf_ptr, &buffer_size);
	unpack16 (&job_desc_ptr->shared, &buf_ptr, &buffer_size);
	
	unpack32 (&job_desc_ptr->time_limit, &buf_ptr, &buffer_size);
	
	unpack32 (&job_desc_ptr->num_procs, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->num_nodes, &buf_ptr, &buffer_size);
	unpack32 (&job_desc_ptr->user_id, &buf_ptr, &buffer_size);
	
	return 0;
}

/* template 
void pack_ ( char ** buffer , uint32_t * length , * msg )
{
	pack16 ( msg -> , buffer , length ) ;
	pack32 ( msg -> , buffer , length ) ;
}

void unpack_ ( char ** buffer , uint32_t * length , * messge )
{
	unpack16 ( & msg -> , buffer , length ) ;
	unpack32 ( & msg -> , buffer , length ) ;
}
*/
