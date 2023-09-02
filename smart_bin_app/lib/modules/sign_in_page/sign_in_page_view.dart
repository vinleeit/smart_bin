import 'package:flutter/material.dart';
import 'package:smart_bin_app/modules/sign_in_page/sign_in_page_controller.dart';

class SignInPageView extends StatelessWidget {
  final _controller = const SignInPageController();

  const SignInPageView({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 60.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              Column(
                children: [
                  const CircleAvatar(
                    radius: 80.0,
                    child: Icon(
                      Icons.delete,
                      size: 60.0,
                    ),
                  ),
                  const SizedBox(height: 15.0),
                  Text(
                    'Smart Bin App',
                    style: Theme.of(context).textTheme.headlineMedium,
                  ),
                ],
              ),
              Column(
                children: [
                  TextFormField(
                    decoration: const InputDecoration(
                      labelText: 'Username',
                    ),
                  ),
                  const SizedBox(height: 15.0),
                  TextFormField(
                    decoration: const InputDecoration(
                      labelText: 'Password',
                    ),
                  ),
                ],
              ),
              ElevatedButton(
                onPressed: () => _controller.onSignIn(context),
                child: const Text('Sign In'),
              )
            ],
          ),
        ),
      ),
    );
  }
}
