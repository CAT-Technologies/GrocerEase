# Bluetooth RSSI signal strength scanner android app

This is a basic Android app project built on top of existing reference blog [Punch Through](https://punchthrough.com)'s "Ultimate Guide to Android BLE Development" blog post for beginners, with examples of how to perform basic Android BLE operations like the following:
While the original app has a lot of functionalities, we modify the same for only basic functionalities like:

- Scanning for nearby BLE/bluetooth devices
- Connecting to bluetooth devices
- Discovering RSSI values of nearby devices


## Setup

1. Clone the project to your directory of choice.

```
git clone https://github.com/CAT-Technologies/GrocerEase/tree/mobile-app-with-ble/mobile-app
```

2. Launch Android Studio and select "Open an existing Android Studio project".

3. Navigate to the directory where you cloned the project to, and double click on it.

4. Wait for Gradle sync to complete.

5. You can now use Android USB debugging to test the app or else use AVD emulator

## Requirements

This project targets Android 10 and has a min SDK requirement of 21 (Android 5.0)

## Contributing

### Reporting bugs

Please [open an issue](https://github.com/CAT-Technologies/GrocerEase/issues) to report a bug if the app isn't behaving as expected.

### Opening a Pull Request

Please fork the repository and create a feature branch before opening a Pull Request against the `devel` branch.

### Linting and code style

The project uses Kotlin's default [coding conventions](https://kotlinlang.org/docs/reference/coding-conventions.html) and includes the `.idea/codeStyle` directory in source control. The project also runs [`ktlint`](https://ktlint.github.io) as part of the CI process to ensure code consistency.

You may run `ktlint` locally using the following command:

```
./gradlew ktlint
```

Some simpler violations can be automatically formatted by `ktlint` using the following command:

```
./gradlew ktlintFormat
```