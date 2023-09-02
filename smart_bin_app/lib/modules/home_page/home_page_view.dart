import 'package:flutter/material.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:smart_bin_app/modules/home_page/home_page_controller.dart';

class HomePageView extends StatelessWidget {
  final _conroller = const HomePageController();

  const HomePageView({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Devices'),
        centerTitle: true,
        leading: IconButton(
          icon: const Icon(Icons.menu),
          onPressed: () {},
        ),
        actions: [
          IconButton(
            onPressed: () => _conroller.onSignOut(context),
            icon: const Icon(Icons.logout),
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _conroller.onAddDevice(context),
        child: const Icon(
          Icons.add,
        ),
      ),
      bottomNavigationBar: BottomNavigationBar(
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.device_hub),
            label: 'devices',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.supervised_user_circle),
            label: 'users',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.person),
            label: 'profile',
          ),
        ],
      ),
      body: ListView(
        children: [
          for (int i = 0; i < 1; i++)
            Padding(
              padding: const EdgeInsets.symmetric(vertical: 10.0),
              child: Slidable(
                startActionPane: ActionPane(
                  motion: const StretchMotion(),
                  extentRatio: 1,
                  children: [
                    SlidableAction(
                      backgroundColor: Colors.redAccent,
                      icon: Icons.delete,
                      onPressed: (_) {},
                    ),
                    SlidableAction(
                      backgroundColor: Colors.black26,
                      icon: Icons.info_outline,
                      onPressed: (_) {},
                    ),
                  ],
                ),
                child: Card(
                  margin: const EdgeInsets.only(
                    left: 0,
                    right: 15.0,
                    top: 0.0,
                    bottom: 0.0,
                  ),
                  shape: const RoundedRectangleBorder(
                    borderRadius: BorderRadius.horizontal(
                      right: Radius.circular(30.0),
                    ),
                  ),
                  child: ListTile(
                    title: Text('Device $i'),
                    minVerticalPadding: 30.0,
                    shape: const RoundedRectangleBorder(
                      borderRadius: BorderRadius.horizontal(
                        right: Radius.circular(30.0),
                      ),
                    ),
                    onTap: () => _conroller.onOpenDevice(context),
                  ),
                ),
              ),
            ),
        ],
      ),
    );
  }
}
