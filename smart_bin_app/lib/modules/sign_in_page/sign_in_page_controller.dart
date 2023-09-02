import 'package:flutter/cupertino.dart';
import 'package:smart_bin_app/modules/app_route.dart';

class SignInPageController {
  const SignInPageController();

  void onSignIn(BuildContext context) {
    Navigator.popAndPushNamed(context, AppRoute.home);
  }
}