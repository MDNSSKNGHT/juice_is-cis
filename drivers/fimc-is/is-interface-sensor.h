/*
 * Samsung EXYNOS FIMC-IS (Imaging Subsystem) driver.
 *
 * Reconstructed from r9s kernel tree.
 */

#ifndef IS_SENSOR_INTERFACE_H
#define IS_SENSOR_INTERFACE_H

#include <include/ktypes.h>

#include "is-metadata-vendor.h"

struct ae_param {
	union {
		u32 val;
		u32 long_val;
	};
	u32 short_val;
	u32 middle_val;
};

typedef struct {
	/* Normal parameter */
	/* Each CB has a specific parameter type.(Ex. SetSize Cb has size info param.) */
	void *param;
	unsigned int return_value;
} cis_setting_info;

typedef struct {
	unsigned int exposure;
	unsigned int analog_gain;
	unsigned int digital_gain;
	unsigned int long_exposure;
	unsigned int long_analog_gain;
	unsigned int long_digital_gain;
	unsigned int short_exposure;
	unsigned int short_analog_gain;
	unsigned int short_digital_gain;
	unsigned int middle_exposure;
	unsigned int middle_analog_gain;
	unsigned int middle_digital_gain;
} ae_setting;

typedef struct {
	unsigned int long_exposure_coarse;
	unsigned int long_exposure_fine;
	unsigned int long_exposure_analog_gain;
	unsigned int long_exposure_digital_gain;
	unsigned int long_exposure_companion_digital_gain;
	unsigned int short_exposure_coarse;
	unsigned int short_exposure_fine;
	unsigned int short_exposure_analog_gain;
	unsigned int short_exposure_digital_gain;
	unsigned int short_exposure_companion_digital_gain;
} preprocessor_ae_setting;

typedef struct {
	bool stream_on;

	unsigned int config_idx;
	bool bypass;
	bool paf_stat_enable;
	bool caf_stat_enable;
	bool wdr_enable;
	bool enable_lsc;
	bool enable_drc;
	bool enable_pdaf_bpc;
	bool enable_xtalk;

	enum camera2_sensor_hdr_mode sensor_hdr_mode;
	enum camera2_wdr_mode wdr_mode;
	enum camera2_wdr_mode pre_wdr_mode;
	enum camera2_disparity_mode disparity_mode;
	enum camera2_paf_mode paf_mode;
	enum aa_scene_mode scene_mode;
} is_shared_data;

typedef struct {
	bool ois_available;
	unsigned int mode;
	unsigned int factory_step;
} ois_shared_data;

struct wb_gains {
	u32 gr;
	u32 r;
	u32 b;
	u32 gb;
};

struct roi_setting_t {
	bool    update;
#ifdef SUPPORT_SENSOR_SEAMLESS_3HDR
	u16     roi_start_x[2];
	u16     roi_start_y[2];
	u16     roi_end_x[2];
	u16     roi_end_y[2];
#else
	u16 	roi_start_x;
	u16 	roi_start_y;
	u16 	roi_end_x;
	u16 	roi_end_y;
#endif
};

struct sensor_lsi_3hdr_stat_control_mode_change {
	int r_weight;
	int b_weight;
	int g_weight;
	int low_gate_thr;
	int high_gate_thr;
	struct roi_setting_t y_sum_roi;
};

struct sensor_lsi_3hdr_stat_control_per_frame {
	int r_weight;
	int b_weight;
	int g_weight;
};

struct sensor_imx_3hdr_stat_control_mode_change {
		struct roi_setting_t y_sum_roi;
};

struct sensor_imx_3hdr_stat_control_per_frame {
	u8 pgain;
	u8 ngain;
	u8 fc_correct_intensity;
	u16 wbd_r_gr;
};

struct sensor_imx_3hdr_lsc_table_init {
		u16 ram_table[13*10*2];
};

struct sensor_imx_3hdr_tone_control {
	bool gmt_tc2_enable;
	u8 gmt_tc2_ratio;
	u8 manual21_frame_p1;
	u8 manual21_frame_p2;
	u8 manual12_frame_p1;
	u8 manual12_frame_p2;
	u8 manual_tc_ratio;
	u8 ltc_ratio;
	u16 hdr_tc_ratio_1;
	u16 hdr_tc_ratio_2;
	u16 hdr_tc_ratio_3;
	u16 hdr_tc_ratio_4;
	u16 hdr_tc_ratio_5;
};

struct sensor_imx_3hdr_ev_control {
	u8 evc_pgain;
	u8 evc_ngain;
};

typedef struct {
	/** The length of a frame is specified as a number of lines, frame_length_lines.
	  @remarks
	  'frame length lines' is changed in dynamic AE mode.
	 */
	unsigned int frame_length_lines;
	unsigned int frame_time; // unit: ms

	/** The length of a line is specified as a number of pixel clocks, line_length_pck. */
	unsigned int line_length_pck;
	unsigned int line_readOut_time; // unit: ns
	unsigned long long rolling_shutter_skew;

	/** Video Timing Pixel Clock, vt_pix_clk_freq. */
	u64 pclk;
	unsigned int min_frame_us_time;
#ifdef CAMERA_REAR2
	unsigned int min_sync_frame_us_time;
#endif

	/** Frame valid time */
	unsigned int frame_valid_us_time;

	unsigned int min_coarse_integration_time;
	unsigned int max_coarse_integration_time;
	unsigned int min_fine_integration_time;
	unsigned int max_fine_integration_time;
	unsigned int max_margin_coarse_integration_time;
	unsigned int max_margin_fine_integration_time;
	unsigned int min_analog_gain[2]; // 0: code, 1: times
	unsigned int max_analog_gain[2];
	unsigned int min_digital_gain[2];
	unsigned int max_digital_gain[2];
	unsigned int cur_coarse_integration_time_step;

	unsigned int cur_frame_us_time;
	unsigned int cur_width;
	unsigned int cur_height;
	unsigned int cur_pattern_mode;
	unsigned int pre_width;
	unsigned int pre_height;

	/** Current analogue_gain_code_global */
	unsigned int cur_exposure_coarse;
	unsigned int cur_exposure_fine;
	unsigned int cur_analog_gain;
	unsigned int cur_analog_gain_permille;
	unsigned int cur_digital_gain;
	unsigned int cur_digital_gain_permille;
	unsigned int cur_long_exposure_coarse;
	unsigned int cur_long_exposure_fine;
	unsigned int cur_long_analog_gain;
	unsigned int cur_long_analog_gain_permille;
	unsigned int cur_long_digital_gain;
	unsigned int cur_long_digital_gain_permille;
	unsigned int cur_short_exposure_coarse;
	unsigned int cur_short_exposure_fine;
	unsigned int cur_short_analog_gain;
	unsigned int cur_short_analog_gain_permille;
	unsigned int cur_short_digital_gain;
	unsigned int cur_short_digital_gain_permille;

	unsigned int stream_on;

	/* Moved from SensorEntry.cpp Jong 20121008 */
	unsigned int sen_vsync_count;
	unsigned int sen_frame_id;
	unsigned int stream_id;
	unsigned int product_name; /* sensor names such as IMX134, IMX135, and S5K3L2 */
	unsigned int sens_config_index_cur;
	unsigned int sens_config_index_pre;
	unsigned int sens_config_ex_mode_cur;
	unsigned int cur_frame_rate;
	unsigned int pre_frame_rate;
	bool is_active_area;

	/* bool bFirstRegSet; */
	unsigned int low_expo_start;

	/* To deal with N + 1 or N +2 setting timing, 0: Previous input, 1: Current input */
	unsigned int analog_gain[2];
	unsigned int digital_gain[2];

	unsigned int max_fps;

	unsigned int mipi_err_int_cnt[10];
	unsigned int mipi_err_print_out_cnt[10];

	bool called_common_sensor_setting; /* [hc0105.kim, 2013/09/13] Added to avoid calling common sensor register setting again. */
/* #ifdef C1_LSC_CHANGE // [ist.song 2014.08.19] Added to inform videomode to sensor. */
	bool video_mode;
#ifdef USE_NEW_PER_FRAME_CONTROL
	unsigned int num_of_frame;
#endif
/* #endif */
	unsigned int actuator_position;

	is_shared_data is_data;
	ois_shared_data ois_data;
	ae_setting auto_exposure[2];
	preprocessor_ae_setting preproc_auto_exposure[2];

/*	SysSema_t pFlashCtrl_IsrSema; //[2014.08.13, kh14.koo] to add for sema of KTD2692 (flash dirver) */

	bool binning; /* If binning is set, sensor should binning for size */
	bool dual_slave;
	bool lte_multi_capture_mode;
	bool highres_capture_mode;

	/* set aeb mode */
	u32 cur_aeb_mode;
	u32 pre_aeb_mode;

	u32 cis_rev;
	u32 cis_model_id;
	u32 group_param_hold;

	/* set low noise mode */
	u32 cur_lownoise_mode;
	u32 pre_lownoise_mode;

	/* set 12bit mode */
	u32 cur_12bit_mode;
	u32 pre_12bit_mode;

	u32 frame_length_lines_shifter;

	/* for deliver crop coordinate for RTA */
	u32	crop_x;
	u32	crop_y;
} cis_shared_data;

struct v4l2_subdev;
struct v4l2_rect;
typedef int (*cis_func_type)(struct v4l2_subdev *subdev, cis_setting_info *info);
struct is_cis_ops {
        int (*cis_init)(struct v4l2_subdev *subdev);
        int (*cis_deinit)(struct v4l2_subdev *subdev);
        int (*cis_log_status)(struct v4l2_subdev *subdev);
        int (*cis_group_param_hold)(struct v4l2_subdev *subdev, bool hold);
        int (*cis_set_global_setting)(struct v4l2_subdev *subdev);
        int (*cis_mode_change)(struct v4l2_subdev *subdev, u32 mode);
        int (*cis_set_size)(struct v4l2_subdev *subdev, cis_shared_data *cis_data);
        int (*cis_stream_on)(struct v4l2_subdev *subdev);
        int (*cis_stream_off)(struct v4l2_subdev *subdev);
        int (*cis_adjust_frame_duration)(struct v4l2_subdev *subdev,
						u32 input_exposure_time,
						u32 *target_duration);
	/* Set dynamic frame duration value */
        int (*cis_set_frame_duration)(struct v4l2_subdev *subdev, u32 frame_duration);
	/* Set min fps value */
        int (*cis_set_frame_rate)(struct v4l2_subdev *subdev, u32 min_fps);
        int (*cis_get_min_exposure_time)(struct v4l2_subdev *subdev, u32 *min_expo);
        int (*cis_get_max_exposure_time)(struct v4l2_subdev *subdev, u32 *max_expo);
	cis_func_type cis_adjust_expoure_time; /* TBD */
        int (*cis_set_exposure_time)(struct v4l2_subdev *subdev, struct ae_param *target_exposure);
        int (*cis_get_min_analog_gain)(struct v4l2_subdev *subdev, u32 *min_again);
        int (*cis_get_max_analog_gain)(struct v4l2_subdev *subdev, u32 *max_again);
        int (*cis_adjust_analog_gain)(struct v4l2_subdev *subdev, u32 input_again, u32 *target_permile);
        int (*cis_set_analog_gain)(struct v4l2_subdev *subdev, struct ae_param *again);
        int (*cis_get_analog_gain)(struct v4l2_subdev *subdev, u32 *again);
        int (*cis_get_min_digital_gain)(struct v4l2_subdev *subdev, u32 *min_dgain);
        int (*cis_get_max_digital_gain)(struct v4l2_subdev *subdev, u32 *max_dgain);
	cis_func_type cis_adjust_digital_gain; /* TBD */
        int (*cis_set_digital_gain)(struct v4l2_subdev *subdev, struct ae_param *dgain);
        int (*cis_get_digital_gain)(struct v4l2_subdev *subdev, u32 *dgain);
	int (*cis_compensate_gain_for_extremely_br)(struct v4l2_subdev *subdev, u32 expo, u32 *again, u32 *dgain);
	cis_func_type cis_get_line_readout_time_ns; /* TBD */
	cis_func_type cis_read_sysreg; /* TBD */
	cis_func_type cis_read_userreg; /* TBD */
	int (*cis_wait_streamoff)(struct v4l2_subdev *subdev);
	int (*cis_wait_streamon)(struct v4l2_subdev *subdev);
	void (*cis_data_calculation)(struct v4l2_subdev *subdev, u32 mode);
	int (*cis_set_long_term_exposure)(struct v4l2_subdev *subdev);
	int (*cis_set_adjust_sync)(struct v4l2_subdev *subdev, u32 adjust_sync);
#ifdef USE_CAMERA_SENSOR_RETENTION
	int (*cis_retention_prepare)(struct v4l2_subdev *subdev);
	int (*cis_retention_crc_check)(struct v4l2_subdev *subdev);
#endif
#ifdef USE_CAMERA_EMBEDDED_HEADER
	int (*cis_get_frame_id)(struct v4l2_subdev *subdev, u8 *embedded_buf, u16 *frame_id);
#endif
	int (*cis_set_frs_control)(struct v4l2_subdev *subdev, u32 command);
	int (*cis_set_super_slow_motion_roi)(struct v4l2_subdev *subdev, struct v4l2_rect *ssm_roi);
	int (*cis_set_super_slow_motion_setting)(struct v4l2_subdev *subdev, struct v4l2_rect *setting);
#ifdef CAMERA_REAR2_SENSOR_SHIFT_CROP
	int (*cis_update_pdaf_tail_size)(struct v4l2_subdev *subdev, struct is_sensor_cfg *select);
#endif
	int (*cis_check_rev_on_init)(struct v4l2_subdev *subdev);
	int (*cis_set_super_slow_motion_threshold)(struct v4l2_subdev *subdev, u32 threshold);
	int (*cis_get_super_slow_motion_threshold)(struct v4l2_subdev *subdev, u32 *threshold);
	int (*cis_set_initial_exposure)(struct v4l2_subdev *subdev);
	int (*cis_get_super_slow_motion_gmc)(struct v4l2_subdev *subdev, u32 *gmc);
	int (*cis_get_super_slow_motion_frame_id)(struct v4l2_subdev *subdev, u32 *frameid);
	int (*cis_set_super_slow_motion_flicker)(struct v4l2_subdev *subdev, u32 flicker);
	int (*cis_get_super_slow_motion_flicker)(struct v4l2_subdev *subdev, u32 *flicker);
	int (*cis_get_super_slow_motion_md_threshold)(struct v4l2_subdev *subdev, u32 *threshold);
	int (*cis_set_super_slow_motion_gmc_table_idx)(struct v4l2_subdev *subdev, u32 idx);
	int (*cis_set_super_slow_motion_gmc_block_with_md_low)(struct v4l2_subdev *subdev, u32 idx);
	int (*cis_recover_stream_on)(struct v4l2_subdev *subdev);
	int (*cis_recover_stream_off)(struct v4l2_subdev *subdev);
	int (*cis_set_laser_control)(struct v4l2_subdev *subdev, u32 onoff);
	int (*cis_set_laser_mode)(struct v4l2_subdev *subdev, u32 mode);
	int (*cis_set_factory_control)(struct v4l2_subdev *subdev, u32 command);
	int (*cis_set_laser_current)(struct v4l2_subdev *subdev, u32 value);
	int (*cis_get_laser_photo_diode)(struct v4l2_subdev *subdev, u16 *value);
	int (*cis_get_tof_tx_freq)(struct v4l2_subdev *subdev, u32 *value);
	int (*cis_get_tof_laser_error_flag)(struct v4l2_subdev *subdev, u32 mode, int *value);
	int (*cis_set_tof_tx_freq)(struct v4l2_subdev *subdev, u32 value);
	int (*cis_set_wb_gains)(struct v4l2_subdev *subdev, struct wb_gains wb_gains);
	int (*cis_set_roi_stat)(struct v4l2_subdev *subdev, struct roi_setting_t roi_control);
	int (*cis_set_3hdr_stat)(struct v4l2_subdev *subdev, bool streaming, void *data);
	void (*cis_check_wdr_mode)(struct v4l2_subdev *subdev, u32 mode_idx);
	int (*cis_check_model_id)(struct v4l2_subdev *subdev);
	int (*cis_active_test)(struct v4l2_subdev *subdev);
	int (*cis_set_dual_setting)(struct v4l2_subdev *subdev, u32 mode);
	int (*cis_get_binning_ratio)(struct v4l2_subdev *subdev, u32 mode, int *binning_ratio);
	int (*cis_init_3hdr_lsc_table)(struct v4l2_subdev *subdev, void *data);
	int (*cis_set_tone_stat)(struct v4l2_subdev *subdev, struct sensor_imx_3hdr_tone_control tone_control);
	int (*cis_set_ev_stat)(struct v4l2_subdev *subdev, struct sensor_imx_3hdr_ev_control ev_control);
	int (*cis_set_totalgain)(struct v4l2_subdev *subdev, struct ae_param *target_exposure, struct ae_param *again, struct ae_param *dgain);
	int (*cis_set_fake_retention)(struct v4l2_subdev *subdev, bool enable);
	int (*cis_wait_ln_mode_delay)(struct v4l2_subdev *subdev);
	int (*cis_set_test_pattern)(struct v4l2_subdev *subdev, camera2_sensor_ctl_t *sensor_ctl);
};

#endif /* IS_SENSOR_INTERFACE_H */
