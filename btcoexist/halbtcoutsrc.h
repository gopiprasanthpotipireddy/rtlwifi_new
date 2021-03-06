#ifndef	__HALBTC_OUT_SRC_H__
#define __HALBTC_OUT_SRC_H__

#define		NORMAL_EXEC					false
#define		FORCE_EXEC						true

extern u8	gl_btc_trace_buf[];
#define		BTC_SPRINTF(ptr, ...)	snprintf(ptr, ##__VA_ARGS__)
#define		BTC_TRACE(fmt)						\
	do {								\
		struct rtl_priv *rtlpriv = gl_bt_coexist.adapter;	\
		if (rtlpriv == NULL)					\
			break;						\
		RT_TRACE_STRING(rtlpriv, COMP_COEX, DBG_LOUD, fmt);		\
	} while (0)

#define		BTC_RF_OFF					0x0
#define		BTC_RF_ON					0x1

#define		BTC_RF_A					0x0
#define		BTC_RF_B					0x1
#define		BTC_RF_C					0x2
#define		BTC_RF_D					0x3

#define		BTC_SMSP				SINGLEMAC_SINGLEPHY
#define		BTC_DMDP				DUALMAC_DUALPHY
#define		BTC_DMSP				DUALMAC_SINGLEPHY
#define		BTC_MP_UNKNOWN		0xff

#define		BT_COEX_ANT_TYPE_PG			0
#define		BT_COEX_ANT_TYPE_ANTDIV		1
#define		BT_COEX_ANT_TYPE_DETECTED	2

#define		BTC_MIMO_PS_STATIC			0	/* 1ss */
#define		BTC_MIMO_PS_DYNAMIC			1	/* 2ss */

#define		BTC_RATE_DISABLE			0
#define		BTC_RATE_ENABLE				1

/* single Antenna definition */
#define		BTC_ANT_PATH_WIFI			0
#define		BTC_ANT_PATH_BT				1
#define		BTC_ANT_PATH_PTA			2
/* dual Antenna definition */
#define		BTC_ANT_WIFI_AT_MAIN		0
#define		BTC_ANT_WIFI_AT_AUX			1
/* coupler Antenna definition */
#define		BTC_ANT_WIFI_AT_CPL_MAIN	0
#define		BTC_ANT_WIFI_AT_CPL_AUX		1

enum btc_powersave_type {
	BTC_PS_WIFI_NATIVE			= 0,	/* wifi original power save behavior */
	BTC_PS_LPS_ON				= 1,
	BTC_PS_LPS_OFF				= 2,
	BTC_PS_MAX
};

enum btc_bt_reg_type {
	BTC_BT_REG_RF						= 0,
	BTC_BT_REG_MODEM					= 1,
	BTC_BT_REG_BLUEWIZE					= 2,
	BTC_BT_REG_VENDOR					= 3,
	BTC_BT_REG_LE						= 4,
	BTC_BT_REG_MAX
};

enum btc_chip_interface {
	BTC_INTF_UNKNOWN	= 0,
	BTC_INTF_PCI			= 1,
	BTC_INTF_USB			= 2,
	BTC_INTF_SDIO		= 3,
	BTC_INTF_MAX
};

enum btc_chip_type {
	BTC_CHIP_UNDEF		= 0,
	BTC_CHIP_CSR_BC4		= 1,
	BTC_CHIP_CSR_BC8		= 2,
	BTC_CHIP_RTL8723A	= 3,
	BTC_CHIP_RTL8821	= 4,
	BTC_CHIP_RTL8723B	= 5,
	BTC_CHIP_MAX
};

/* following is for wifi link status */
#define		WIFI_STA_CONNECTED				BIT(0)
#define		WIFI_AP_CONNECTED				BIT(1)
#define		WIFI_HS_CONNECTED				BIT(2)
#define		WIFI_P2P_GO_CONNECTED			BIT(3)
#define		WIFI_P2P_GC_CONNECTED			BIT(4)

struct btc_board_info {
	/* The following is some board information */
	u8 bt_chip_type;
	u8 pg_ant_num;	/* pg ant number */
	u8 btdm_ant_num;	/* ant number for btdm */
	u8 btdm_ant_num_by_ant_det;	/* ant number for btdm after antenna
					 * detection */
	u8 btdm_ant_pos;	/* Bryant Add to indicate Antenna Position for
				 * (pg_ant_num = 2) && (btdm_ant_num =1)
				 * (DPDT+1Ant case) */
	u8 single_ant_path;	/* current used for 8723b only, 1=>s0,  0=>s1 */
	bool tfbga_package;	/* for Antenna detect threshold  */
	bool btdm_ant_det_finish;
};


/* following is for command line utility */
#define CL_PRINTF(ptr)			halbtc_dbg_info_print(btcoexist, ptr)
#define	CL_SPRINTF(ptr, ...)	snprintf(ptr, ##__VA_ARGS__)

#define		BT_TMP_BUF_SIZE				100

#define RT_TRACE_BTC(comp, level, fmt, ...)				\
	do {								\
		struct rtl_priv *rtlpriv = gl_bt_coexist.adapter;	\
		if (rtlpriv == NULL)					\
			break;						\
		RT_TRACE(rtlpriv, comp, level, fmt, ##__VA_ARGS__);	\
	} while (0)

struct btcoex_dbg_info {
	u8 *info;
	u32 size; /* buffer total size */
	u32 len; /* now used length */
};


enum btc_dbg_opcode {
	BTC_DBG_SET_COEX_NORMAL				= 0x0,
	BTC_DBG_SET_COEX_WIFI_ONLY				= 0x1,
	BTC_DBG_SET_COEX_BT_ONLY				= 0x2,
	BTC_DBG_SET_COEX_DEC_BT_PWR				= 0x3,
	BTC_DBG_SET_COEX_BT_AFH_MAP				= 0x4,
	BTC_DBG_SET_COEX_BT_IGNORE_WLAN_ACT		= 0x5,
	BTC_DBG_MAX
};

enum btc_rssi_state {
	BTC_RSSI_STATE_HIGH						= 0x0,
	BTC_RSSI_STATE_MEDIUM					= 0x1,
	BTC_RSSI_STATE_LOW						= 0x2,
	BTC_RSSI_STATE_STAY_HIGH					= 0x3,
	BTC_RSSI_STATE_STAY_MEDIUM				= 0x4,
	BTC_RSSI_STATE_STAY_LOW					= 0x5,
	BTC_RSSI_MAX
};
#define	BTC_RSSI_HIGH(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_HIGH ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_HIGH) ? true : false)
#define	BTC_RSSI_MEDIUM(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_MEDIUM ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_MEDIUM) ? true : false)
#define	BTC_RSSI_LOW(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_LOW ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_LOW) ? true : false)

enum btc_wifi_role {
	BTC_ROLE_STATION						= 0x0,
	BTC_ROLE_AP								= 0x1,
	BTC_ROLE_IBSS							= 0x2,
	BTC_ROLE_HS_MODE						= 0x3,
	BTC_ROLE_MAX
};

enum btc_wireless_freq {
	BTC_FREQ_2_4G					= 0x0,
	BTC_FREQ_5G						= 0x1,
	BTC_FREQ_MAX
};

enum btc_wifi_bw_mode {
	BTC_WIFI_BW_LEGACY					= 0x0,
	BTC_WIFI_BW_HT20					= 0x1,
	BTC_WIFI_BW_HT40					= 0x2,
	BTC_WIFI_BW_HT80					= 0x3,
	BTC_WIFI_BW_HT160					= 0x4,
	BTC_WIFI_BW_MAX
};

enum btc_wifi_traffic_dir {
	BTC_WIFI_TRAFFIC_TX					= 0x0,
	BTC_WIFI_TRAFFIC_RX					= 0x1,
	BTC_WIFI_TRAFFIC_MAX
};

enum btc_wifi_pnp {
	BTC_WIFI_PNP_WAKE_UP					= 0x0,
	BTC_WIFI_PNP_SLEEP						= 0x1,
	BTC_WIFI_PNP_MAX
};

enum btc_iot_peer {
	BTC_IOT_PEER_UNKNOWN = 0,
	BTC_IOT_PEER_REALTEK = 1,
	BTC_IOT_PEER_REALTEK_92SE = 2,
	BTC_IOT_PEER_BROADCOM = 3,
	BTC_IOT_PEER_RALINK = 4,
	BTC_IOT_PEER_ATHEROS = 5,
	BTC_IOT_PEER_CISCO = 6,
	BTC_IOT_PEER_MERU = 7,
	BTC_IOT_PEER_MARVELL = 8,
	BTC_IOT_PEER_REALTEK_SOFTAP = 9,/* peer is RealTek SOFT_AP, by Bohn, 2009.12.17 */
	BTC_IOT_PEER_SELF_SOFTAP = 10, /* Self is SoftAP */
	BTC_IOT_PEER_AIRGO = 11,
	BTC_IOT_PEER_REALTEK_JAGUAR_BCUTAP = 12,
	BTC_IOT_PEER_REALTEK_JAGUAR_CCUTAP = 13,
	BTC_IOT_PEER_MAX,
};

/* for 8723b-d cut large current issue */
enum bt_wifi_coex_state {
	BTC_WIFI_STAT_INIT,
	BTC_WIFI_STAT_IQK,
	BTC_WIFI_STAT_NORMAL_OFF,
	BTC_WIFI_STAT_MP_OFF,
	BTC_WIFI_STAT_NORMAL,
	BTC_WIFI_STAT_ANT_DIV,
	BTC_WIFI_STAT_MAX
};

enum bt_ant_type {
	BTC_ANT_TYPE_0,
	BTC_ANT_TYPE_1,
	BTC_ANT_TYPE_2,
	BTC_ANT_TYPE_3,
	BTC_ANT_TYPE_4,
	BTC_ANT_TYPE_MAX
};

/* defined for bfp_btc_get */
enum btc_get_type {
	/* type bool */
	BTC_GET_BL_HS_OPERATION,
	BTC_GET_BL_HS_CONNECTING,
	BTC_GET_BL_WIFI_CONNECTED,
	BTC_GET_BL_WIFI_BUSY,
	BTC_GET_BL_WIFI_SCAN,
	BTC_GET_BL_WIFI_LINK,
	BTC_GET_BL_WIFI_ROAM,
	BTC_GET_BL_WIFI_4_WAY_PROGRESS,
	BTC_GET_BL_WIFI_UNDER_5G,
	BTC_GET_BL_WIFI_AP_MODE_ENABLE,
	BTC_GET_BL_WIFI_ENABLE_ENCRYPTION,
	BTC_GET_BL_WIFI_UNDER_B_MODE,
	BTC_GET_BL_EXT_SWITCH,
	BTC_GET_BL_WIFI_IS_IN_MP_MODE,
	BTC_GET_BL_IS_ASUS_8723B,

	/* type s32 */
	BTC_GET_S4_WIFI_RSSI,
	BTC_GET_S4_HS_RSSI,

	/* type u32 */
	BTC_GET_U4_WIFI_BW,
	BTC_GET_U4_WIFI_TRAFFIC_DIRECTION,
	BTC_GET_U4_WIFI_FW_VER,
	BTC_GET_U4_WIFI_LINK_STATUS,
	BTC_GET_U4_BT_PATCH_VER,
	BTC_GET_U4_VENDOR,

	/* type u8 */
	BTC_GET_U1_WIFI_DOT11_CHNL,
	BTC_GET_U1_WIFI_CENTRAL_CHNL,
	BTC_GET_U1_WIFI_HS_CHNL,
	BTC_GET_U1_AP_NUM,
	BTC_GET_U1_ANT_TYPE,
	BTC_GET_U1_IOT_PEER,

	/* ===== for 1Ant ====== */
	BTC_GET_U1_LPS_MODE,

	BTC_GET_MAX
};

enum btc_vendor {
	BTC_VENDOR_LENOVO,
	BTC_VENDOR_ASUS,
	BTC_VENDOR_OTHER
};

/* defined for bfp_btc_set */
enum btc_set_type {
	/* type bool */
	BTC_SET_BL_BT_DISABLE,
	BTC_SET_BL_BT_TRAFFIC_BUSY,
	BTC_SET_BL_BT_LIMITED_DIG,
	BTC_SET_BL_FORCE_TO_ROAM,
	BTC_SET_BL_TO_REJ_AP_AGG_PKT,
	BTC_SET_BL_BT_CTRL_AGG_SIZE,
	BTC_SET_BL_INC_SCAN_DEV_NUM,
	BTC_SET_BL_BT_TX_RX_MASK,
	BTC_SET_BL_MIRACAST_PLUS_BT,

	/* type u8 */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON,
	BTC_SET_U1_AGG_BUF_SIZE,

	/* type trigger some action */
	BTC_SET_ACT_GET_BT_RSSI,
	BTC_SET_ACT_AGGREGATE_CTRL,
	BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,

	/* ===== for 1Ant ====== */
	/* type bool */

	/* type u8 */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE,
	BTC_SET_U1_LPS_VAL,
	BTC_SET_U1_RPWM_VAL,
	/* type trigger some action */
	BTC_SET_ACT_LEAVE_LPS,
	BTC_SET_ACT_ENTER_LPS,
	BTC_SET_ACT_NORMAL_LPS,
	BTC_SET_ACT_DISABLE_LOW_POWER,
	BTC_SET_ACT_UPDATE_RAMASK,
	BTC_SET_ACT_SEND_MIMO_PS,
	/* BT Coex related */
	BTC_SET_ACT_CTRL_BT_INFO,
	BTC_SET_ACT_CTRL_BT_COEX,
	BTC_SET_ACT_CTRL_8723B_ANT,
	/* ================= */
	BTC_SET_MAX
};

enum btc_dbg_disp_type {
	BTC_DBG_DISP_COEX_STATISTICS			= 0x0,
	BTC_DBG_DISP_BT_LINK_INFO				= 0x1,
	BTC_DBG_DISP_WIFI_STATUS				= 0x2,
	BTC_DBG_DISP_MAX
};

enum btc_notify_type_ips {
	BTC_IPS_LEAVE							= 0x0,
	BTC_IPS_ENTER							= 0x1,
	BTC_IPS_MAX
};
enum btc_notify_type_lps {
	BTC_LPS_DISABLE							= 0x0,
	BTC_LPS_ENABLE							= 0x1,
	BTC_LPS_MAX
};
enum btc_notify_type_scan {
	BTC_SCAN_FINISH							= 0x0,
	BTC_SCAN_START							= 0x1,
	BTC_SCAN_MAX
};
enum btc_notify_type_associate {
	BTC_ASSOCIATE_FINISH						= 0x0,
	BTC_ASSOCIATE_START						= 0x1,
	BTC_ASSOCIATE_MAX
};
enum btc_notify_type_media_status {
	BTC_MEDIA_DISCONNECT					= 0x0,
	BTC_MEDIA_CONNECT						= 0x1,
	BTC_MEDIA_MAX
};
enum btc_notify_type_special_packet {
	BTC_PACKET_UNKNOWN					= 0x0,
	BTC_PACKET_DHCP							= 0x1,
	BTC_PACKET_ARP							= 0x2,
	BTC_PACKET_EAPOL						= 0x3,
	BTC_PACKET_MAX
};
enum btc_notify_type_stack_operation {
	BTC_STACK_OP_NONE					= 0x0,
	BTC_STACK_OP_INQ_PAGE_PAIR_START		= 0x1,
	BTC_STACK_OP_INQ_PAGE_PAIR_FINISH	= 0x2,
	BTC_STACK_OP_MAX
};

/* map to btc_notify_type_stack_operation */
enum hci_ext_bt_operation {
	HCI_BT_OP_NONE = 0x0,
	HCI_BT_OP_INQUIRY_START = 0x1,
	HCI_BT_OP_INQUIRY_FINISH = 0x2,
	HCI_BT_OP_PAGING_START = 0x3,
	HCI_BT_OP_PAGING_SUCCESS = 0x4,
	HCI_BT_OP_PAGING_UNSUCCESS = 0x5,
	HCI_BT_OP_PAIRING_START = 0x6,
	HCI_BT_OP_PAIRING_FINISH = 0x7,
	HCI_BT_OP_BT_DEV_ENABLE = 0x8,
	HCI_BT_OP_BT_DEV_DISABLE = 0x9,
	HCI_BT_OP_MAX
};

/* Bryant Add */
enum btc_antenna_pos {
	BTC_ANTENNA_AT_MAIN_PORT				= 0x1,
	BTC_ANTENNA_AT_AUX_PORT				= 0x2,
};

typedef u8(*bfp_btc_r1)(void *btc_context, u32 reg_addr);

typedef u16(*bfp_btc_r2)(void *btc_context, u32 reg_addr);

typedef u32(*bfp_btc_r4)(void *btc_context, u32 reg_addr);

typedef void (*bfp_btc_w1)(void *btc_context, u32 reg_addr, u8 data);

typedef void (*bfp_btc_w1_bit_mask)(void *btc_context, u32 reg_addr,
				    u8 bit_mask, u8 data1b);

typedef void (*bfp_btc_w2)(void *btc_context, u32 reg_addr, u16 data);

typedef void (*bfp_btc_w4)(void *btc_context, u32 reg_addr, u32 data);

typedef void (*bfp_btc_local_reg_w1)(void *btc_context, u32 reg_addr, u8 data);

typedef void (*bfp_btc_set_bb_reg)(void *btc_context, u32 reg_addr,
				   u32 bit_mask, u32 data);

typedef u32(*bfp_btc_get_bb_reg)(void *btc_context, u32 reg_addr, u32 bit_mask);

typedef void (*bfp_btc_set_rf_reg)(void *btc_context, u8 rf_path, u32 reg_addr,
				   u32 bit_mask, u32 data);

typedef u32(*bfp_btc_get_rf_reg)(void *btc_context, u8 rf_path, u32 reg_addr,
				 u32 bit_mask);

typedef void (*bfp_btc_fill_h2c)(void *btc_context, u8 element_id, u32 cmd_len,
				 u8 *cmd_buffer);


typedef bool (*bfp_btc_get)(void *btcoexist, u8 get_type, void *out_buf);


typedef bool (*bfp_btc_set)(void *btcoexist, u8 set_type, void *in_buf);

typedef void (*bfp_btc_set_bt_reg)(void *btc_context, u8 reg_type, u32 offset,
				   u32 value);

typedef bool (*bfp_btc_set_bt_ant_detection)(void *btc_context, u8 tx_time,
		u8 bt_chnl);

typedef u32(*bfp_btc_get_bt_reg)(void *btc_context, u8 reg_type, u32 offset);

typedef void (*bfp_btc_disp_dbg_msg)(void *btcoexist, u8 disp_type);


struct btc_bt_info {
	bool					bt_disabled;
	u8					rssi_adjust_for_agc_table_on;
	u8					rssi_adjust_for_1ant_coex_type;
	bool					pre_bt_ctrl_agg_buf_size;
	bool					bt_ctrl_agg_buf_size;
	bool					pre_reject_agg_pkt;
	bool					reject_agg_pkt;
	bool					increase_scan_dev_num;
	bool					bt_tx_rx_mask;
	u8					pre_agg_buf_size;
	u8					agg_buf_size;
	bool					bt_busy;
	bool					limited_dig;
	u16					bt_hci_ver;
	u16					bt_real_fw_ver;
	u8					bt_fw_ver;
	u32					get_bt_fw_ver_cnt;
	bool					miracast_plus_bt;

	bool					bt_disable_low_pwr;

	bool					bt_ctrl_lps;
	bool					bt_lps_on;
	bool					force_to_roam;	/* for 1Ant solution */
	u8					lps_val;
	u8					rpwm_val;
	u32					ra_mask;
};

struct btc_stack_info {
	bool					profile_notified;
	u16					hci_version;	/* stack hci version */
	u8					num_of_link;
	bool					bt_link_exist;
	bool					sco_exist;
	bool					acl_exist;
	bool					a2dp_exist;
	bool					hid_exist;
	u8					num_of_hid;
	bool					pan_exist;
	bool					unknown_acl_exist;
	s8					min_bt_rssi;
};

struct btc_bt_link_info {
	bool					bt_link_exist;
	bool					bt_hi_pri_link_exist;
	bool					sco_exist;
	bool					sco_only;
	bool					a2dp_exist;
	bool					a2dp_only;
	bool					hid_exist;
	bool					hid_only;
	bool					pan_exist;
	bool					pan_only;
	bool					slave_role;
	bool					acl_busy;
};

struct btc_statistics {
	u32					cnt_bind;
	u32					cnt_power_on;
	u32					cnt_pre_load_firmware;
	u32					cnt_init_hw_config;
	u32					cnt_init_coex_dm;
	u32					cnt_ips_notify;
	u32					cnt_lps_notify;
	u32					cnt_scan_notify;
	u32					cnt_connect_notify;
	u32					cnt_media_status_notify;
	u32					cnt_special_packet_notify;
	u32					cnt_bt_info_notify;
	u32					cnt_rf_status_notify;
	u32					cnt_periodical;
	u32					cnt_coex_dm_switch;
	u32					cnt_stack_operation_notify;
	u32					cnt_dbg_ctrl;
};

struct btc_coexist {
	bool				binded;		/* make sure only one adapter can bind the data context */
	void				*adapter;		/* default adapter */
	struct  btc_board_info		board_info;
	struct  btc_bt_info
		bt_info;		/* some bt info referenced by non-bt module */
	struct  btc_stack_info		stack_info;
	struct  btc_bt_link_info	bt_link_info;
	enum  btc_chip_interface	chip_interface;

	bool				initilized;
	bool				stop_coex_dm;
	bool				manual_control;
	u8				*cli_buf;
	struct  btcoex_dbg_info		dbg_info;
	struct  btc_statistics		statistics;
	u8				pwr_mode_val[10];

	/* function pointers */
	/* io related */
	bfp_btc_r1			btc_read_1byte;
	bfp_btc_w1			btc_write_1byte;
	bfp_btc_w1_bit_mask	btc_write_1byte_bitmask;
	bfp_btc_r2			btc_read_2byte;
	bfp_btc_w2			btc_write_2byte;
	bfp_btc_r4			btc_read_4byte;
	bfp_btc_w4			btc_write_4byte;
	bfp_btc_local_reg_w1	btc_write_local_reg_1byte;
	/* read/write bb related */
	bfp_btc_set_bb_reg	btc_set_bb_reg;
	bfp_btc_get_bb_reg	btc_get_bb_reg;

	/* read/write rf related */
	bfp_btc_set_rf_reg	btc_set_rf_reg;
	bfp_btc_get_rf_reg	btc_get_rf_reg;

	/* fill h2c related */
	bfp_btc_fill_h2c		btc_fill_h2c;
	/* other */
	bfp_btc_disp_dbg_msg	btc_disp_dbg_msg;
	/* normal get/set related */
	bfp_btc_get			btc_get;
	bfp_btc_set			btc_set;

	bfp_btc_get_bt_reg	btc_get_bt_reg;
	bfp_btc_set_bt_reg	btc_set_bt_reg;

	bfp_btc_set_bt_ant_detection	btc_set_bt_ant_detection;
};

extern struct  btc_coexist				gl_bt_coexist;

bool exhalbtc_initlize_variables(void);
bool exhalbtc_bind_bt_coex_withadapter(void *adapter);
void exhalbtc_power_on_setting(struct btc_coexist *btcoexist);
void exhalbtc_pre_load_firmware(struct btc_coexist *btcoexist);
void exhalbtc_init_hw_config(struct btc_coexist *btcoexist, bool wifi_only);
void exhalbtc_init_coex_dm(struct btc_coexist *btcoexist);
void exhalbtc_ips_notify(struct btc_coexist *btcoexist, u8 type);
void exhalbtc_lps_notify(struct btc_coexist *btcoexist, u8 type);
void exhalbtc_scan_notify(struct btc_coexist *btcoexist, u8 type);
void exhalbtc_connect_notify(struct btc_coexist *btcoexist, u8 action);
void exhalbtc_media_status_notify(struct btc_coexist *btcoexist,
				  enum rt_media_status media_status);
void exhalbtc_special_packet_notify(struct btc_coexist *btcoexist, u8 pkt_type);
void exhalbtc_bt_info_notify(struct btc_coexist *btcoexist, u8 *tmp_buf,
			     u8 length);
void exhalbtc_rf_status_notify(struct btc_coexist *btcoexist, u8 type);
void exhalbtc_stack_operation_notify(struct btc_coexist *btcoexist, u8 type);
void exhalbtc_halt_notify(struct btc_coexist *btcoexist);
void exhalbtc_pnp_notify(struct btc_coexist *btcoexist, u8 pnp_state);
void exhalbtc_coex_dm_switch(struct btc_coexist *btcoexist);
void exhalbtc_periodical(struct btc_coexist *btcoexist);
void exhalbtc_dbg_control(struct btc_coexist *btcoexist, u8 op_code, u8 op_len,
			  u8 *pdata);
void exhalbtc_antenna_detection(struct btc_coexist *btcoexist, u32 cent_freq,
				u32 offset, u32 span, u32 seconds);
void exhalbtc_stack_update_profile_info(void);
void exhalbtc_set_hci_version(u16 hci_version);
void exhalbtc_set_bt_patch_version(u16 bt_hci_version, u16 bt_patch_version);
void exhalbtc_update_min_bt_rssi(s8 bt_rssi);
#if 0
void exhalbtc_set_bt_exist(bool bt_exist);
#endif
void exhalbtc_set_chip_type(u8 chip_type);
void exhalbtc_set_ant_num(u8 type, u8 ant_num);
void exhalbtc_set_single_ant_path(u8 single_ant_path);
void exhalbtc_display_bt_coex_info(struct btc_coexist *btcoexist);
void exhalbtc_display_ant_detection(struct btc_coexist *btcoexist);

/**************for 8812AE BTCOEX**************/
void rtl_btcoex_SendEventExtBtCoexControl(struct rtl_priv *rtlpriv,
		u8 bNeedDbgRsp, u8 dataLen, void *pData);
void rtl_btcoex_SendEventExtBtInfoControl(struct rtl_priv *rtlpriv, u8 dataLen,
		void *pData);

void rtl_btcoex_dump_tx_msg(u8 *tx_msg, u8 len, u8 *msg_name);
u8 rtl_btcoex_sendmsgbysocket(struct rtl_priv *rtlpriv, u8 *msg, u8 msg_size,
			      bool force);
void rtl_btcoex_SendScanNotify(struct rtl_priv *rtlpriv, u8 scanType);
void rtl_btcoex_init_socket(struct rtl_priv *rtlpriv);
void rtl_btcoex_close_socket(struct rtl_priv *rtlpriv);

bool halbtc_is_wifi_uplink(struct rtl_priv *adapter);

void halbtc_dbg_info_init(struct btc_coexist *btcoexist, u8 *buf, u32 size);
void halbtc_dbg_info_print(struct btc_coexist *btcoexist, u8 *dbgmsg);

#endif
