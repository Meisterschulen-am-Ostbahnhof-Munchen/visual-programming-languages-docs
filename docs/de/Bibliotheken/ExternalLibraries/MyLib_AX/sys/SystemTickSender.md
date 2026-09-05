# SystemTickSender

![SystemTickSender_network](./SystemTickSender_network.svg)

* * * * * * * * * *

## Einleitung

`SystemTickSender` liefert ein zyklisch hochzählendes "Lebenszeichen" für VT und Web-Client — eine einfache, sofort sichtbare Bestätigung, dass die Steuerung läuft und Ereignisse verarbeitet. Der Baustein wird in mehreren Trainingsbeispielen dieses Systems eingesetzt, u. a. in [`InputOutputTesterButton_DIDO_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md) und [`InputOutputTesterButton_PWM_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md).

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: SystemTickSender

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **System_Tick** (SubApp, `MyLib::sys`): liefert einen zyklisch hochzählenden Wert als `ADI`-Adapter (DINT).
    - **ADI_SPLIT_2**: `adapter::events::unidirectional::ADI_SPLIT_2` — verzweigt den Zähler-Adapter in zwei Richtungen.
    - **ADI_TO_AUDI**: `adapter::conversion::unidirectional::ADI_TO_AUDI` — wandelt DINT-Adapter in UDINT-Adapter um (numerisch korrekt, siehe [Numerisch vs. bitweise](../../../../Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/Numerisch_vs_Bitweise.md): `ANY_INT`→`ANY_INT` ist ein sicherer Cast).
    - **Q_NumericValue_AUDI**: `isobus::UT::Q::Q_NumericValue_AUDI` — schreibt den Zählerwert in ein VT-Zahlenfeld.
    - **ADI_PUBLISH_1**: `adapter::net::ADI_PUBLISH_1` — OPC-UA-Publish des rohen DINT-Zählerwerts an den Web-Client.
- **Funktionsweise**: Der intern erzeugte Zähler wird einmal für die VT-Anzeige (über UDINT-Zwischenschritt, da `Q_NumericValue_AUDI` diesen Typ erwartet) und einmal roh als DINT für OPC-UA-Publish verwendet.

## Programmablauf und Verbindungen

1. `System_Tick.ADI_OUT` → `ADI_SPLIT_2.IN`.
2. `ADI_SPLIT_2.OUT1` → `ADI_TO_AUDI.ADI_IN` → `ADI_TO_AUDI.AUDI_OUT` → `Q_NumericValue_AUDI.u32NewValue` (VT-Anzeige).
3. `ADI_SPLIT_2.OUT2` → `ADI_PUBLISH_1.IN` (OPC-UA-Publish).
4. Parameter: `u16ObjId` → `Q_NumericValue_AUDI.u16ObjId`; `ID_WRITE` → `ADI_PUBLISH_1.ID`.

## Technische Besonderheiten

- **Zwei parallele Verwendungen desselben Zählers**: VT-Anzeige (über `ADI_TO_AUDI`, da `Q_NumericValue_AUDI` einen UDINT-Adapter erwartet) und OPC-UA-Publish (direkt als DINT) laufen unabhängig über `ADI_SPLIT_2`.
- **Numerisch korrekte Konvertierung**: `ADI_TO_AUDI` (DINT→UDINT) ist ein `ANY_INT`→`ANY_INT`-Cast, kein Bit-Reinterpretations-Trap wie z. B. [`AD_TO_AR`](../../../../Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/AD_AR/AD_TO_AR.md).

## Anwendungsszenarien

- "Herzschlag"-Anzeige auf VT und Web-UI, um auf einen Blick zu erkennen, dass die Steuerung aktiv ist und nicht abgestürzt/eingefroren ist.

## Zusammenfassung

`SystemTickSender` ist ein einfacher, aber in fast jedem Trainingsbeispiel dieses Systems wiederverwendeter Baustein, der einen zyklischen Zählerwert parallel an VT-Zahlenfeld und OPC-UA-Web-Client verteilt — ein minimales, aber wirksames Lebenszeichen der Steuerung.

## 🛠️ Zugehörige Übungen

- [InputOutputTesterButton_DIDO_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)
- [InputOutputTesterButton_PWM_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
