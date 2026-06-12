# FIELDBUS_BYTE_TO_SIGNAL


![FIELDBUS_BYTE_TO_SIGNAL](./FIELDBUS_BYTE_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_BYTE_TO_SIGNAL** dient der einfachen Validierung eines BYTE-Signals aus einem Feldbus. Er gibt den Eingangswert nur dann unverändert an den Ausgang weiter, wenn dieser innerhalb eines definierten gültigen Bereichs liegt. Das Ergebnis der Validierung wird über einen separaten booleschen Ausgang signalisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ | Event | Normaler Ausführungsanstoß; verarbeitet den aktuellen Wert am Eingang IN. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF | Event | Bestätigung der Ausführung; die Ausgänge OUT und VALID wurden aktualisiert. |

### **Daten-Eingänge**
| Name | Datentyp | Initialwert | Kommentar |
|------|----------|-------------|-----------|
| IN | BYTE | NOT_AVAILABLE_B | Eingangssignal als Byte-Wert. |

### **Daten-Ausgänge**
| Name | Datentyp | Initialwert | Kommentar |
|------|----------|-------------|-----------|
| OUT | BYTE | 16#00 | Gefilterter Ausgangswert; 0 wenn Signal ungültig. |
| VALID | BOOL | FALSE | TRUE, wenn das Eingangssignal als gültig erkannt wurde. |

### **Adapter**
Keine.

## Funktionsweise
Der Block prüft bei jedem REQ-Ereignis den aktuellen BYTE-Eingangswert **IN** gegen eine vorgegebene Konstante **VALID_SIGNAL_B** (aus dem Import `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`).  
Die Logik im Algorithmus lautet:

```structuredtext
IF (BYTE_TO_USINT(IN) <= BYTE_TO_USINT(VALID_SIGNAL_B)) THEN
    OUT := IN;
    VALID := TRUE;
ELSE
    OUT := BYTE#0;
    VALID := FALSE;
END_IF;
```

- Ist der Wert von **IN** (als vorzeichenloser Integer interpretiert) **kleiner oder gleich** dem Schwellwert **VALID_SIGNAL_B**, wird der Eingang direkt auf **OUT** durchgereicht und **VALID** auf `TRUE` gesetzt.
- Überschreitet **IN** den Schwellwert, wird **OUT** auf `0` zurückgesetzt und **VALID** auf `FALSE`.

Nach der Berechnung wird das Ereignis **CNF** ausgegeben. Der Initialwert von **IN** liegt mit `NOT_AVAILABLE_B` bereits außerhalb des gültigen Bereichs, sodass der Block nach dem ersten Durchlauf standardmäßig auf „ungültig“ steht.

## Technische Besonderheiten
- Der Filter basiert auf **zwei externen Konstanten** aus der Bibliothek `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`:  
  - `NOT_AVAILABLE_B` – definiert den Wert für „Signal nicht verfügbar“ (Initialwert von IN).  
  - `VALID_SIGNAL_B` – definiert die obere Grenze für gültige Signale.  
- Die Umwandlung `BYTE_TO_USINT` stellt sicher, dass die Werte als Zahlen 0…255 verglichen werden können.
- Der Block ist als **SimpleFB** mit nur einem Zustand (**REQ**) realisiert – keine Zustandsmaschine mit mehreren Schritten.
- Lizenz: Eclipse Public License 2.0.

## Zustandsübersicht
Der Funktionsblock besitzt genau einen Ausführungszustand:

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ | Führt den Algorithmus **REQ** aus (Filterlogik) | CNF |

Es gibt keine weiteren Warte- oder Initialisierungszustände.

## Anwendungsszenarien
- **Feldbus-Signalvalidierung**: Ein Sensor liefert einen BYTE-Wert, der nur innerhalb eines bestimmten Bereichs (z. B. 0…100) physikalisch sinnvoll ist. Der Block verhindert, dass fehlerhafte oder unplausible Werte in die Steuerungslogik gelangen.
- **Sicherheitsbezogene Systeme**: Kann als einfacher Bereichsprüfer für analoge oder digitale Feldbussignale in der Automatisierungstechnik (z. B. Landwirtschaft, Maschinensteuerung) eingesetzt werden.
- **Signalweiche**: Trennung von gültigen und ungültigen Datenströmen – z. B. zur Ansteuerung eines UND-Filters oder zur Fehlererkennung.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen **Schwellwertschaltern** (z. B. `HYSTERESIS` oder `LIMIT_ALARM`) arbeitet dieser Block rein auf BYTE-Ebene und gibt den Originalwert direkt aus, solange er im Gültigkeitsbereich liegt – keine Hysterese oder Alarmfunktion.
- Gegenüber einem **Multiplexer** (`MUX`) benötigt er kein zweites Steuersignal, sondern trifft die Entscheidung automatisch anhand des Eingangswertes.
- Ähnliche Blöcke in IEC 61499 existieren oft als `RANGE_CHECK` oder `VALIDATE`, sind aber meist auf generische Datentypen ausgelegt. Dieser Block ist speziell auf das in Feldbussen übliche BYTE-Format zugeschnitten.

## Fazit
**FIELDBUS_BYTE_TO_SIGNAL** ist ein kompakter, spezialisierter Filterbaustein zur Gültigkeitsprüfung von BYTE-Signalen. Er erfordert keine Konfiguration von Grenzen, da diese über die importierten Konstanten in der Bibliothek definiert sind. Durch die klare Trennung von Datenausgang und Gültigkeitssignal eignet er sich hervorragend für die Aufbereitung von Feldbusdaten in sicherheitskritischen oder fehlertoleranten Automatisierungssystemen.