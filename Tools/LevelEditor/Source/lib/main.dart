import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:window_manager/window_manager.dart';

const double blockSize = 30;
const double buttonHeight = 50;
void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();
  if (Platform.isWindows) {
    WindowManager.instance.setMinimumSize(const Size(blockSize * 13 + 15, blockSize * 15 + buttonHeight + 50));
    WindowManager.instance.setMaximumSize(const Size(blockSize * 13 + 15, blockSize * 15 + buttonHeight + 50));
  }

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Pengo Level Editor',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const GridScreen(),
    );
  }
}

class GridScreen extends StatefulWidget {
  const GridScreen({Key? key}) : super(key: key);

  @override
  State<GridScreen> createState() => _GridScreenState();
}

class Block
{
  bool activated = false;
}

class _GridScreenState extends State<GridScreen>
{
  List<Block> blocks = List.generate(13 * 15, (i) { return Block(); });

  void blockTapped(int block)
  {
    setState(() {
      blocks[block].activated = !blocks[block].activated;
    });
  }

  void export()
  {
    String export = "";
    for(int i = 0; i < blocks.length; ++i)
    {
      if(blocks[i].activated) export += "$i, ";
    }
    if(export.length >= 2) export = export.substring(0, export.length - 2);
    Clipboard.setData(ClipboardData(text: export));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Column(
        children: [
          grid(context),
          SizedBox(
            width: 250,
            height: buttonHeight,
            child: TextButton(
              onPressed: export,
              child: const Text("Export active tiles to clipboard"),
            ),
          ),
        ],
      ),
    );
  }

  Widget grid(BuildContext context)
  {
    return SizedBox(
      width: blockSize * 13,
      height: blockSize * 15,
      child: GridView.count(
        crossAxisCount: 13,
        children: List.generate(13 * 15, (index) {
          return Center(
            child: InkWell(
              onTap: () => blockTapped(index),
              child: Container(
                  width: blockSize - 2,
                  height: blockSize - 2,
                  color: Colors.black,
                  child: blocks[index].activated ? Image.asset(
                    "assets/images/block.png",
                    fit: BoxFit.fill
                  ) : null,
              ),
            ),
          );
        }),
      ),
    );
  }
}
