# F_FRACTION_TO_PERCENT

![F_FRACTION_TO_PERCENT](./F_FRACTION_TO_PERCENT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **F_FRACTION_TO_PERCENT** ist das Gegenstück zu [`F_PERCENT_TO_FRACTION`](./F_PERCENT_TO_FRACTION.md): Er rechnet einen Anteil (REAL 0.0–1.0), wie ihn `MyLib::sys::F_PWM_RAW_TO_PERCENT` liefert, in einen Prozentwert (REAL 0.0–100.0) um, der z. B. per OPC-UA-Publish an einen Web-Client gesendet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ | Event | Umrechnung anfordern; verarbeitet den aktuellen Wert von `rFraction`. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF | Event | Umrechnung abgeschlossen; `rPercent` wurde aktualisiert. |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| rFraction | REAL | Anteil 0.0-1.0. |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| rPercent | REAL | Prozentwert 0.0-100.0. |

### **Adapter**

Keine.

## Funktionsweise

Bei jedem `REQ`-Ereignis wird der Eingang `rFraction` unbegrenzt mit 100 multipliziert:

```structuredtext
rPercent := rFraction * 100.0;
```

Anschließend wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten

- Realisiert als **SimpleFB** mit nur einem Ausführungszustand (`REQ`) — keine mehrstufige Zustandsmaschine.
- Im Gegensatz zum Gegenstück `F_PERCENT_TO_FRACTION` **kein Klemmen** des Eingangswerts: Da `rFraction` in der PWM-Kette bereits durch `RampLimitFS`/`F_PWM_RAW_TO_PERCENT` auf 0.0-1.0 begrenzt ist, ist eine zusätzliche Bereichsprüfung hier nicht nötig.
- Bewusst getrennt von `MyLib::sys::F_PWM_RAW_TO_PERCENT`, das den Fieldbus-Rohwert (nicht Prozent!) in den Anteil umrechnet — beide Bausteine zusammen bilden die vollständige Kette Fieldbus-Rohwert → Anteil → Prozent.
- Lizenz: Eclipse Public License 2.0.

## Zustandsübersicht

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ | Führt den Algorithmus **REQ** aus (Multiplikation mit 100) | CNF |

Es gibt keine weiteren Warte- oder Initialisierungszustände.

## Anwendungsszenarien

- Rückrechnung eines intern verarbeiteten Anteils (0.0-1.0) auf den Prozentwert, den ein Web-Client per OPC-UA-Publish erwartet — z. B. im PWM-Trainingsbeispiel [`RampLimitFS_TO_logiBUS_QDA_PWM_OPC`](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md).
- Allgemein: jede Schnittstelle, die intern mit einem normierten Anteil 0.0-1.0 rechnet, extern aber in Prozent kommuniziert.

## Vergleich mit ähnlichen Bausteinen

- Gegenstück ist [`F_PERCENT_TO_FRACTION`](./F_PERCENT_TO_FRACTION.md) (Prozent → Anteil, für die Vorwärtsrichtung, inklusive Klemmen).
- Einfachste denkbare Skalenwandler ohne jede Bereichsprüfung, da der Eingang bereits garantiert normiert ankommt.

## Fazit

**F_FRACTION_TO_PERCENT** ist eine reine Multiplikation mit 100, die den intern verwendeten Anteil 0.0-1.0 auf den extern kommunizierten Prozentwert 0.0-100.0 bringt — ohne eigene Fehlerbehandlung, da der Eingang bereits vor-normiert ist.

## 🛠️ Zugehörige Übungen

- [RampLimitFS_TO_logiBUS_QDA_PWM_OPC](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md)
- [InputOutputTesterButton_PWM_OPC_UA](../../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
