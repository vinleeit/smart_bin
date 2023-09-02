import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';
import 'package:percent_indicator/circular_percent_indicator.dart';

class DeviceTile extends StatelessWidget {
  final String title;
  final Widget description;

  const DeviceTile({
    Key? key,
    required this.title,
    required this.description,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 16.0),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Text(
            title,
            style: Theme.of(context).textTheme.titleMedium,
          ),
          description,
        ],
      ),
    );
  }
}

class DevicePageView extends StatelessWidget {
  final _gradientColor = const [
    Colors.grey,
    Colors.black,
  ];

  final _data = const [
    FlSpot(0, 0),
    FlSpot(1, 0.17),
    FlSpot(2, 0.66),
    FlSpot(3, 1.5),
    FlSpot(4, 2.67),
    FlSpot(5, 4.8),
    FlSpot(6, 6),
  ];

  const DevicePageView({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Stack(
          children: [
            SingleChildScrollView(
              padding: const EdgeInsets.only(top: 36.0, bottom: 24.0),
              physics: const BouncingScrollPhysics(),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  Padding(
                    padding: const EdgeInsets.symmetric(horizontal: 50.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: [
                        Padding(
                          padding: const EdgeInsets.symmetric(vertical: 25.0),
                          child: Center(
                            child: Card(
                              shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(100.0)),
                              elevation: 5.0,
                              child: ClipRRect(
                                borderRadius: BorderRadius.circular(100.0),
                                child: CircularPercentIndicator(
                                  radius: 80.0,
                                  backgroundColor: Colors.white,
                                  percent: 0.2,
                                  circularStrokeCap: CircularStrokeCap.round,
                                  lineWidth: 10.0,
                                  fillColor: Colors.greenAccent,
                                  progressColor: Colors.grey,
                                  center: Column(
                                    mainAxisAlignment: MainAxisAlignment.center,
                                    children: [
                                      const Icon(
                                        Icons.delete_outline_rounded,
                                        size: 64.0,
                                      ),
                                      Text(
                                        '20%',
                                        style: Theme.of(context).textTheme.titleMedium,
                                      ),
                                    ],
                                  ),
                                ),
                              ),
                            ),
                          ),
                        ),
                        const DeviceTile(
                          title: 'Device',
                          description: Text('Device 0'),
                        ),
                        const DeviceTile(
                          title: 'ID',
                          description: Text('2ZR5YS19XW'),
                        ),
                        OutlinedButton(
                          onPressed: () {},
                          child: const Text('View Secret'),
                        ),
                        const Divider(height: 36.0),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              'Insights',
                              style: Theme.of(context).textTheme.headlineSmall,
                            ),
                            TextButton(
                              onPressed: () {},
                              child: const Text('view'),
                            )
                          ],
                        ),
                      ],
                    ),
                  ),
                  Card(
                    margin: const EdgeInsets.symmetric(vertical: 16.0, horizontal: 24.0),
                    child: Padding(
                      padding: const EdgeInsets.symmetric(vertical: 24.0, horizontal: 36.0),
                      child: Column(
                        children: [
                          Text(
                            '26 August 2023',
                            style: Theme.of(context).textTheme.titleMedium,
                          ),
                          const SizedBox(height: 10.0),
                          SizedBox(
                            height: 250.0,
                            child: LineChart(
                              LineChartData(
                                gridData: FlGridData(
                                  show: true,
                                  drawVerticalLine: true,
                                  horizontalInterval: 1,
                                  verticalInterval: 1,
                                  getDrawingHorizontalLine: (value) {
                                    return const FlLine(
                                      color: Colors.grey,
                                      strokeWidth: 1.0,
                                    );
                                  },
                                  getDrawingVerticalLine: (value) {
                                    return const FlLine(
                                      color: Colors.grey,
                                      strokeWidth: 1.0,
                                    );
                                  },
                                ),
                                titlesData: FlTitlesData(
                                  show: true,
                                  rightTitles: const AxisTitles(
                                    sideTitles: SideTitles(showTitles: false),
                                  ),
                                  topTitles: const AxisTitles(
                                    sideTitles: SideTitles(showTitles: false),
                                  ),
                                  bottomTitles: AxisTitles(
                                    sideTitles: SideTitles(
                                      showTitles: true,
                                      interval: 1,
                                      getTitlesWidget: (double value, TitleMeta meta) {
                                        return SideTitleWidget(
                                          axisSide: meta.axisSide,
                                          child: Center(
                                            child: Text(
                                              (value % 2 == 0) ? '${value + 6 < 10 ? "0" : ""}${(value + 6).toInt()}:00' : '',
                                              style: Theme.of(context).textTheme.labelMedium,
                                            ),
                                          ),
                                        );
                                      },
                                    ),
                                  ),
                                  leftTitles: AxisTitles(
                                    sideTitles: SideTitles(
                                      showTitles: true,
                                      interval: 1,
                                      getTitlesWidget: (double value, TitleMeta meta) {
                                        return Text(
                                          (value % 2 == 0) ? '${(value * 5).toInt()}' : '',
                                          style: Theme.of(context).textTheme.labelMedium,
                                        );
                                      },
                                    ),
                                  ),
                                ),
                                borderData: FlBorderData(
                                  show: true,
                                  border: const Border(
                                    left: BorderSide(),
                                    bottom: BorderSide(),
                                  ),
                                ),
                                minX: 0,
                                maxX: (_data.length - 1).toDouble(),
                                minY: 0,
                                maxY: _data.length.toDouble(),
                                lineBarsData: [
                                  LineChartBarData(
                                    spots: _data,
                                    isCurved: true,
                                    gradient: LinearGradient(
                                      colors: _gradientColor,
                                    ),
                                    barWidth: 5,
                                    isStrokeCapRound: true,
                                    dotData: const FlDotData(
                                      show: false,
                                    ),
                                    belowBarData: BarAreaData(
                                      show: true,
                                      gradient: LinearGradient(
                                        colors: _gradientColor.map((color) => color.withOpacity(0.5)).toList(),
                                      ),
                                    ),
                                  ),
                                ],
                              ),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              ),
            ),
            Positioned(
              left: 5.0,
              child: Card(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(100.0)),
                child: IconButton(
                  onPressed: () => Navigator.pop(context),
                  tooltip: 'Back',
                  icon: const Icon(Icons.arrow_back),
                ),
              ),
            )
          ],
        ),
      ),
    );
  }
}
