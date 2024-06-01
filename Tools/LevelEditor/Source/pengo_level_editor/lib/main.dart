import 'dart:convert';
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

enum BlockState { none, block, unhatched, diamond }

class Block
{
  BlockState state = BlockState.none;
}

class _GridScreenState extends State<GridScreen>
{
  List<Block> blocks = List.generate(13 * 15, (i) { return Block(); });

  void blockTapped(int block)
  {
    setState(() {
      if (blocks[block].state == BlockState.none) blocks[block].state = BlockState.block;
      else if (blocks[block].state == BlockState.block) blocks[block].state = BlockState.unhatched;
      else if (blocks[block].state == BlockState.unhatched) blocks[block].state = BlockState.diamond;
      else if (blocks[block].state == BlockState.diamond) blocks[block].state = BlockState.none;
    });
  }

  void export()
  {
    String blockList = "";
    for (int i = 0; i < blocks.length; i++)
    {
      if (blocks[i].state == BlockState.none) continue;

      blockList += "$i, ";
    }
    blockList = blockList.substring(0, blockList.length - 2);

    String unhatchedList = "";
    for (int i = 0; i < blocks.length; i++)
    {
      if (blocks[i].state != BlockState.unhatched) continue;

      unhatchedList += "$i, ";
    }
    unhatchedList = unhatchedList.substring(0, unhatchedList.length - 2);

    String diamondList = "";
    for (int i = 0; i < blocks.length; i++)
    {
      if (blocks[i].state != BlockState.diamond) continue;

      diamondList += "$i, ";
    }
    diamondList = diamondList.substring(0, diamondList.length - 2);


    String export =
  """
  {
  "blocks": [ $blockList ],
  "unhatched": [ $unhatchedList ],
  "diamond": [ $diamondList ]
  }
  """;



    Clipboard.setData(ClipboardData(text: export));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Column(
        children: [
          grid(context),
         Row(
           children: [
             SizedBox(
               width: 250,
               height: buttonHeight,
               child: TextButton(
                 onPressed: export,
                 child: const Text("Export json to clipboard"),
               ),
             ),
             SizedBox(
               width: 100,
               height: buttonHeight,
               child: TextButton(
                 onPressed: () {
                   setState(() {
                     for (Block block in blocks) { block.state = BlockState.none; }
                   });
                 },
                 child: const Text("Clear grid"),
               ),
             ),
           ],
         )
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
          bool hasImage = blocks[index].state != BlockState.none;
          String imagePath = "";
          if (blocks[index].state == BlockState.block) imagePath = "assets/images/block.png";
          else if (blocks[index].state == BlockState.unhatched) imagePath = "assets/images/unhatched.png";
          else if (blocks[index].state == BlockState.diamond) imagePath = "assets/images/diamond.png";

          return Center(
            child: InkWell(
              onTap: () => blockTapped(index),
              child: Container(
                  width: blockSize - 2,
                  height: blockSize - 2,
                  color: Colors.black,
                  child: hasImage ? Image.asset(
                    imagePath,
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
