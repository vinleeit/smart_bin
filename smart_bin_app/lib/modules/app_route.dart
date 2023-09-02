import 'package:flutter/material.dart';
import 'package:smart_bin_app/modules/home_page/home_page_view.dart';
import 'package:smart_bin_app/modules/sign_in_page/sign_in_page_view.dart';

class AppRoute {
  AppRoute._();

  static String signIn = '/sign-in';
  static String home = '/home';
  static String cart = '/cart';

  static Map<String, Widget Function(BuildContext)> get routes {
    return {
      signIn: (_) => const SignInPageView(),
      home: (_) => const HomePageView(),
    };
  }
}
