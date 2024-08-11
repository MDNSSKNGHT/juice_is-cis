/*
 * Samsung EXYNOS FIMC-IS (Imaging Subsystem) driver.
 *
 * Reconstructed from r9s kernel tree.
 */

#ifndef IS_SENSOR_INTERFACE_H
#define IS_SENSOR_INTERFACE_H

#include <include/ktypes.h>

#include "is-metadata-vendor.h"

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

#endif /* IS_SENSOR_INTERFACE_H */
