import 'package:flutter/material.dart';
import 'package:smart_bin_app/modules/app_route.dart';
import 'package:smart_bin_app/modules/device_page/device_page_view.dart';

class HomePageController {
  const HomePageController();

  void onSignOut(BuildContext context) {
    Navigator.popAndPushNamed(context, AppRoute.signIn);
  }

  void onAddDevice(BuildContext context) {
    Navigator.popAndPushNamed(context, AppRoute.signIn);
  }

  void onOpenDevice(BuildContext context) {
    Navigator.push(context, MaterialPageRoute(builder: (_) {
      return const DevicePageView();
    }));
  }
}
