exp_code_gbn:
Makefile�ļ��С�-lpthread����ĳɡ�-pthread��
rdt_gbn_sender.c�ļ��е�278�С�ptr_pkt->state = RDT_PKT_ST_SENT;��������275�С�udt_sendto( sock_fd, ptr_pkt->rdt_pkt, ptr_pkt->pkt_len, 0,(struct sockaddr *)recv_addr_ptr, sizeof(*recv_addr_ptr) );��֮ǰ