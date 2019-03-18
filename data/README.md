# Wifi Positioning Data
The provided data was collected on the fourth floor of the Science Academic Building of Peking University. Due to limited time, we did not collect more data. But if you want to collect your own data, the file format is as follows

## 1 Database File Format

We use different MAC addresses as identifiers for the access point. And the wifi RSSI unit is dBm. numSample is the number of database sampling points.

At each sampling point, we collected 10 times and calculate its mean RSSI as inputs.

| ID        | AP1(dBm) | AP2(dBm) | ...  | APn(dBm) |
| --------- | -------- | -------- | ---- | -------- |
| 1         | -71.2    | -69.0    | ...  | 0.0      |
| 2         | -75.0    | -50.3    | ...  | -60.1    |
| ...       | ...      | ...      | ...  | ...      |
| numSample | -64.7    | -80.6    | ...  | -65.0    |

## 2 Database Position File Format

We didn't use Z coordinate in our data, but this program can also predict 3D positions in practice.

| ID        | X(cm) | Y(cm) | Z(cm) |
| --------- | ----- | ----- | ----- |
| 1         | 1570  | 600   | 0     |
| 2         | 1510  | 750   | 0     |
| ...       | ...   | ...   | ...   |
| numSample | -500  | 800   | 0     |

## 3 Testdata File Format

The timestamp we used is unix epoch time.

| TIMESTAMP  | AP1(dBm) | AP2(dBm) | ...  | APn(dBm) |
| ---------- | -------- | -------- | ---- | -------- |
| 1545121436 | -66.7    | -70.7    | ...  | -65.0    |
| 1545121437 | -67.0    | -80.6    | ...  | -70.1    |
| ...        | ...      | ...      | ...  | ...      |
| 1545121458 | -84.7    | -50.5    | ...  | -80.0    |
