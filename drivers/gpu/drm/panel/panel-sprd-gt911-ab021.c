// SPDX-License-Identifier: GPL-2.0-only
// DRM panel driver for the Anbernic RG Rotate lcd_gt911_mipi_ab021 (720x720)
// MIPI-DSI video-mode panel. Init sequence and timings extracted from the stock
// dtbo overlay (sprd,generic-mipi-panel / lcd_gt911_mipi_ab021).

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct gt911ab021 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline struct gt911ab021 *to_gt911ab021(struct drm_panel *panel)
{
	return container_of(panel, struct gt911ab021, panel);
}

/*
 * Vendor sprd,reset-on-sequence in physical levels: high 50ms, low 50ms,
 * high 120ms (reset is active-low, so it ends de-asserted). reset-gpios is
 * declared GPIO_ACTIVE_LOW, so logical 1 == asserted == physical low.
 */
static void gt911ab021_reset(struct gt911ab021 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(50);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(50);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(120);
}

static int gt911ab021_on(struct gt911ab021 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x52);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0xc2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0xcf);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x30, 0x58);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x9c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0xa7);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x3c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0xfe);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91, 0x77);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x92, 0x77);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa1, 0x50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa3, 0x58);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa4, 0x9c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa7, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa8, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa9, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xaa, 0xfc);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xab, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xac, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xad, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xae, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xaf, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x52);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x32);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x3f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x3f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe, 0x1b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbf, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd4, 0x2e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd5, 0x3f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7, 0x43);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xda, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdb, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdc, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdd, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x52);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x51);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0xeb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0xea);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2c, 0xed);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2d, 0xec);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x53);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x40, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x45, 0xea);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0xe9);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0xec);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0xeb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x51, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x53, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x55, 0xee);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0xed);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0xef);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x92, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x93, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x96, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x97, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x98, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x99, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9a, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa8, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa9, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x52);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x36, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x53, 0x2c);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 200);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 100);
	return dsi_ctx.accum_err;
}

static int gt911ab021_off(struct gt911ab021 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 10);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int gt911ab021_prepare(struct drm_panel *panel)
{
	struct gt911ab021 *ctx = to_gt911ab021(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	gt911ab021_reset(ctx);

	ret = gt911ab021_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int gt911ab021_unprepare(struct drm_panel *panel)
{
	struct gt911ab021 *ctx = to_gt911ab021(panel);

	gt911ab021_off(ctx);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode gt911ab021_mode = {
	.clock = 38400,
	.hdisplay = 720,
	.hsync_start = 720 + 46,
	.hsync_end = 720 + 46 + 2,
	.htotal = 720 + 46 + 2 + 52,
	.vdisplay = 720,
	.vsync_start = 720 + 30,
	.vsync_end = 720 + 30 + 2,
	.vtotal = 720 + 30 + 2 + 25,
	.width_mm = 109,
	.height_mm = 62,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
};

static int gt911ab021_get_modes(struct drm_panel *panel,
				struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &gt911ab021_mode);
}

static const struct drm_panel_funcs gt911ab021_funcs = {
	.prepare = gt911ab021_prepare,
	.unprepare = gt911ab021_unprepare,
	.get_modes = gt911ab021_get_modes,
};

static int gt911ab021_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct gt911ab021 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 2;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE;
	dsi->hs_rate = 551488000;
	dsi->lp_rate = 20000000;

	drm_panel_init(&ctx->panel, dev, &gt911ab021_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void gt911ab021_remove(struct mipi_dsi_device *dsi)
{
	struct gt911ab021 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id gt911ab021_of_match[] = {
	{ .compatible = "sprd,lcd-gt911-mipi-ab021" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, gt911ab021_of_match);

static struct mipi_dsi_driver gt911ab021_driver = {
	.probe = gt911ab021_probe,
	.remove = gt911ab021_remove,
	.driver = {
		.name = "panel-sprd-gt911-ab021",
		.of_match_table = gt911ab021_of_match,
	},
};
module_mipi_dsi_driver(gt911ab021_driver);

MODULE_DESCRIPTION("DRM driver for lcd_gt911_mipi_ab021 720x720 DSI panel");
MODULE_LICENSE("GPL");
