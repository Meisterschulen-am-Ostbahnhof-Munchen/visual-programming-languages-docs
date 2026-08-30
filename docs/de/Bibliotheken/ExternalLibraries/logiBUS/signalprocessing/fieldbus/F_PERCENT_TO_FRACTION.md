# F_PERCENT_TO_FRACTION

![F_PERCENT_TO_FRACTION](./F_PERCENT_TO_FRACTION.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **F_PERCENT_TO_FRACTION** rechnet einen Prozentwert (REAL 0.0–100.0), wie er z. B. über OPC-UA-Subscribe von einem Web-Client empfangen wird, in einen Anteil (REAL 0.0–1.0) um, wie ihn `MyLib::sys::F_PWM_PERCENT_TO_RAW` als Eingang erwartet. Außerhalb des gültigen Bereichs liegende Werte werden geklemmt statt einen Fehler zu erzeugen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ | Event | Umrechnung anfordern; verarbeitet den aktuellen Wert von `rPercent`. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF | Event | Umrechnung abgeschlossen; `rFraction` wurde aktualisiert. |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| rPercent | REAL | Prozentwert, wird auf 0.0-100.0 begrenzt. |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| rFraction | REAL | Anteil 0.0-1.0. |

### **Adapter**

Keine.

## Funktionsweise

Bei jedem `REQ`-Ereignis wird der Eingang `rPercent` geprüft und auf den gültigen Bereich geklemmt:

```structuredtext
IF rPercent <= 0.0 THEN
    rFraction := 0.0;
ELSIF rPercent >= 100.0 THEN
    rFraction := 1.0;
ELSE
    rFraction := rPercent / 100.0;
END_IF;
```

- Werte `<= 0.0` ergeben `rFraction = 0.0`, Werte `>= 100.0` ergeben `rFraction = 1.0`.
- Alle anderen Werte werden linear durch 100 geteilt.
- Anschließend wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten

- Realisiert als **SimpleFB** mit nur einem Ausführungszustand (`REQ`) — keine mehrstufige Zustandsmaschine.
- Klemmt statt zu fehlerbehandeln: unplausible Prozentwerte (z. B. durch fehlerhafte Web-Eingaben) führen nicht zu einem Fehlerzustand, sondern werden stillschweigend auf 0-100 % begrenzt.
- Bewusst getrennt von `MyLib::sys::F_PWM_PERCENT_TO_RAW`, das Anteil (nicht Prozent!) in den Fieldbus-Rohwert umrechnet — beide Bausteine zusammen bilden die vollständige Kette Prozent → Anteil → Fieldbus-Rohwert.
- Lizenz: Eclipse Public License 2.0.

## Zustandsübersicht

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ | Führt den Algorithmus **REQ** aus (Klemmen + Division durch 100) | CNF |

Es gibt keine weiteren Warte- oder Initialisierungszustände.

## Anwendungsszenarien

- Umrechnung eines per OPC-UA-Subscribe empfangenen Web-Sollwerts (Prozent REAL) in den Anteil, den interne Fieldbus-Umrechnungsbausteine erwarten — z. B. im PWM-Trainingsbeispiel [`RampLimitFS_TO_logiBUS_QDA_PWM_OPC`](../../../../../Bibliotheken/typelibrary/MyLib/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md).
- Allgemein: jede Schnittstelle, die extern in Prozent kommuniziert, intern aber mit einem normierten Anteil 0.0-1.0 rechnet.

## Vergleich mit ähnlichen Bausteinen

- Gegenstück ist [`F_FRACTION_TO_PERCENT`](./F_FRACTION_TO_PERCENT.md) (Anteil → Prozent, für die Rückrichtung).
- Im Gegensatz zu den `FIELDBUS_*_TO_SIGNAL`-Bausteinen (z. B. `FIELDBUS_BYTE_TO_SIGNAL`) prüft dieser Baustein keine Gültigkeit gegen eine Konstante, sondern führt eine reine, klemmende Skalenumrechnung durch.

## Fazit

**F_PERCENT_TO_FRACTION** ist ein minimaler, klemmender Skalenwandler, der die Lücke zwischen extern kommuniziertem Prozentwert und intern verwendetem Anteil 0.0-1.0 schließt — ohne eigene Fehlerbehandlung, da außerhalb liegende Werte einfach begrenzt werden.

## 🛠️ Zugehörige Übungen

* [RampLimitFS_TO_logiBUS_QDA_PWM_OPC](../../../../../Bibliotheken/typelibrary/MyLib/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md)
* [InputOutputTesterButton_PWM_OPC_UA](../../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
