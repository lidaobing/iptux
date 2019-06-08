//
// C++ Implementation: DetectPal
//
// Description:
//
//
// Author: Jally <jallyx@163.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "config.h"
#include "DetectPal.h"

#include <glib/gi18n.h>

#include "iptux/UiCoreThread.h"
#include "iptux/callback.h"
#include "iptux/global.h"
#include "iptux-core/output.h"
#include "iptux/UiHelper.h"

namespace iptux {

/**
 * 类构造函数.
 */
DetectPal::DetectPal() : widset(NULL) { g_datalist_init(&widset); }

/**
 * 类析构函数.
 */
DetectPal::~DetectPal() { g_datalist_clear(&widset); }

/**
 * 探测好友入口.
 * @param parent 父窗口指针
 */
void DetectPal::DetectEntry(GtkWidget *parent) {
  GtkWidget *dialog;
  DetectPal dpal;

  /* 创建对话框窗体 */
  dialog = dpal.CreateMainDialog(parent);
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
                     dpal.CreateInputArea(), TRUE, TRUE, 0);

  /* 运行对话框 */
  gtk_widget_show_all(dialog);
mark:
  switch (gtk_dialog_run(GTK_DIALOG(dialog))) {
    case GTK_RESPONSE_ACCEPT:
      dpal.SendDetectPacket();
      goto mark;
    default:
      break;
  }
  gtk_widget_destroy(dialog);
}

/**
 * 创建主对话框.
 * @param parent 父窗口指针
 * @return 对话框
 */
GtkWidget *DetectPal::CreateMainDialog(GtkWidget *parent) {
  GtkWidget *dialog;

  dialog = gtk_dialog_new_with_buttons(
      _("Detect pals"), GTK_WINDOW(parent), GtkDialogFlags(GTK_DIALOG_MODAL),
      _("Detect"), GTK_RESPONSE_ACCEPT, _("Cancel"), GTK_RESPONSE_CANCEL, NULL);
  gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT);
  gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);
  g_datalist_set_data(&widset, "dialog-widget", dialog);

  return dialog;
}

/**
 * 创建接受输入区域.
 * @return 主窗体
 */
GtkWidget *DetectPal::CreateInputArea() {
  GtkWidget *frame;
  GtkWidget *widget;

  frame = gtk_frame_new(_("Please input an IP address (IPv4 only):"));
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);

  widget = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(widget), INET_ADDRSTRLEN);
  g_object_set(widget, "has-tooltip", TRUE, NULL);
  gtk_container_add(GTK_CONTAINER(frame), widget);
  g_signal_connect(widget, "query-tooltip", G_CALLBACK(entry_query_tooltip),
                   _("Please input an IP address (IPv4 only)!"));
  g_signal_connect(widget, "insert-text", G_CALLBACK(entry_insert_numeric),
                   NULL);
  g_datalist_set_data(&widset, "ipv4-entry-widget", widget);

  return frame;
}

/**
 * 发送探测数据包.
 */
void DetectPal::SendDetectPacket() {
  GtkWidget *widget, *parent;
  in_addr_t ipv4;
  const char *text;

  parent = GTK_WIDGET(g_datalist_get_data(&widset, "dialog-widget"));
  widget = GTK_WIDGET(g_datalist_get_data(&widset, "ipv4-entry-widget"));
  gtk_widget_grab_focus(widget);  //为下一次任务做准备

  text = gtk_entry_get_text(GTK_ENTRY(widget));
  if (inet_pton(AF_INET, text, &ipv4) <= 0) {
    pop_warning(parent, _("\nIllegal IP(v4) address: %s!"), text);
    return;
  }

  g_cthrd->SendDetectPacket(ipv4);
  pop_info(parent, _("The notification has been sent to %s."), text);
  gtk_entry_set_text(GTK_ENTRY(widget), "");
}

}  // namespace iptux
