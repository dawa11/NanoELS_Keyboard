# Custom Mechanical Keyboard for NanoELS H5

## 1. Project Overview

This project provides the design and instructions to build a custom mechanical keyboard specifically tailored for the **NanoELS H5**. The NanoELS H5 is an advanced Electronic Lead Screw (ELS) system.

For more information on the NanoELS H5, please visit the official documentation and source code:
[https://github.com/kachurovskiy/nanoels/tree/main/h5](https://github.com/kachurovskiy/nanoels/tree/main/h5)

This keyboard combines all the essential keys documented for the H5 onto a simple, robust switchplate using mechanical switches, providing tactile feedback and a dedicated interface for operating your machine.

![Photo of the finished Switchplate](Images/Finished-Switchplate.jpg])

---

## 2. Bill of Materials (BOM) & Requirements

To complete this build, you will need the following components and tools:

### Components
* **1x Microcontroller:** Must have at least **15 GPIO pins** and be **5V tolerant**.
    * *Recommended:* Arduino Micro or a compatible clone.
* **42x Mechanical Keyboard Switches:** Cherry MX style or clones.
* **Wiring/Cabling:** Thin hook-up wire.

### Tools & Equipment
* **Soldering Iron**
* **3D Printer**

---

## 3. 3D Printed Parts & Printing Guidelines

You have several options for the 3D printed parts, depending on your printer setup and aesthetic preferences.

### Options

#### Switchplate
* **Grooves:** Features visual separation grooves between the different key groups. Ideal for single-color prints.
* **Multi Material:** Has a flat surface modeled as a diferrent material between the key groups, designed for multi-color printing.

#### Keycaps
* **Embedded:** The key legends (labels) are modeled into the surface of the keycap. For single-color printing.
* **Multi Material:** Flat, the key legends are modeled as a diferrent material so they can be printed with two colors. Ideal for multi-color printing of the legends or manual labeling.

### Printing Requirements
* **Switchplate:** Can be printed with a standard **0.4mm nozzle**.
* **Keycaps:** To ensure the embedded or multi-color legends are legible, these **must** be printed with a finer **0.2mm nozzle** (hotend).

---

## 4. Wiring & Schematic

After fitting the 42 switches into the switchplate, they must be wired in a matrix configuration. The following schematic shows how to solder the switches to create a **7 row x 6 column switch matrix**.

![Wiring Schematic]([IMAGE_PATH_TO_WIRING_DIAGRAM])

This matrix is scanned by the microcontroller (e.g., Arduino Micro). The microcontroller translates the keypresses and sends the corresponding data to the NanoELS H5 controller via a **PS/2** interface.

### Controller Connection

To connect the keyboard to the NanoELS controller, use the following pinout:

| Arduino Pins | NanoELS PINS | Function |
| :--- | :--- | :--- |
| **VCC** | **5V** | Power Supply |
| **GND** | **GND** | Ground |
| **2** | **KEYC** | PS/2 Clock |
| **3** | **KEYD** | PS/2 Data |

---

## 5. Planned Improvements (Roadmap)

* **Handwheels:** Addition of mounting points for two incremental rotary encoders (handwheels) on the sides of the switchplate for precise X and Z axis control.

---

## 6. Known Bugs & Limitations

* **Unimplemented Keys:** The button corresponding to `Angle/RPM/Wifi` are currently non-functional.
* **STEP Buttons:** The `STEP +` and `STEP -` buttons currently perform the exact same function.
* **No Ghosting Protection:** The keyboard matrix does **not** include diodes. Pressing multiple keys simultaneously may lead to incorrect key detections ("ghosting"). **Only one key should be pressed at a time.**
