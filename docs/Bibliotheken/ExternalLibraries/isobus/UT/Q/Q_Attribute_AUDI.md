# Q_Attribute_AUDI


![Q_Attribute_AUDI](./Q_Attribute_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **Q_Attribute_AUDI** implementiert das Kommando „Change Attribute“ des ISOBUS-Standards ISO 11783-6 (Teil 6 – F.38). Er ermöglicht das Ändern eines Attributs eines Objekts, das über eine eindeutige Attribut-ID (AID) identifiziert wird. Der Baustein unterstützt die Übergabe des neuen Attributwerts über eine Adapter-Schnittstelle und gibt den alten Wert ebenfalls über einen Adapter zurück. String-Attribute können mit diesem Befehl nicht geändert werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT     | EInit | Initialisiert den Service und startet die Kommunikation mit dem ISOBUS-VT |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO    | EInit | Bestätigt den erfolgreichen Abschluss der Initialisierung |
| CNF      | Event | Bestätigt die Durchführung des angeforderten Attributänderungs-Kommandos |

### **Daten-Eingänge**
| Variable      | Typ   | Beschreibung |
|---------------|-------|--------------|
| u16ObjId      | UINT  | Objekt-ID des zu ändernden Attributs (Initialwert: ID_NULL) |
| u8IdAttribute | USINT | Attribut-ID (AID) – definiert, welches Attribut des Objekts geändert werden soll |

### **Daten-Ausgänge**
| Variable   | Typ    | Beschreibung |
|------------|--------|--------------|
| STATUS     | STRING | Statusmeldung des ausgeführten Dienstes |
| s16result  | INT    | Rückgabewert des Kommandos (Fehlercodes siehe Funktionsweise) |

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| u32ValueAttribute | Socket | unidirectional::AUDI | Neuer Wert für das Attribut (32-Bit, wird über den Adapter in den FB eingespeist) |
| u32OldValueAttribute | Plug | unidirectional::AUDI | Alter Wert des Attributs (32-Bit, wird vom FB über den Adapter ausgegeben) |

## Funktionsweise
1. **Initialisierung**: Nach einem positiven Flanke an **INIT** wird der Dienst initialisiert. Die dafür benötigten Parameter (Objekt-ID und Attribut-ID) werden aus den Daten-Eingängen gelesen.
2. **Ausführung des Kommandos**: Sobald am Socket **u32ValueAttribute** der Ereignisausgang **E1** ausgelöst wird (z. B. durch einen angeschlossenen FB, der einen neuen Wert bereitstellt), wird das Attributänderungs-Kommando gestartet. Der neue Attributwert wird vom Adapter übernommen.
3. **Rückmeldung**: Nach Abschluss des Kommandos wird der Ausgang **CNF** aktiviert. Der STATU-String und der Rückgabewert **s16result** enthalten das Ergebnis. Parallel dazu wird am Plug **u32OldValueAttribute** der zuvor gespeicherte alte Attributwert über den Ereignisausgang **E1** signalisiert und über **D1** bereitgestellt.

Der Baustein delegiert die eigentliche ISOBUS-Kommunikation an den internen Funktionsblock **Q_Attribute**, der die notwendigen Protokollschritte durchführt.

## Technische Besonderheiten
- **Fehlercodes** (über s16result ausgegeben):
  - `VT_E_NO_ERR (0)` – kein Fehler
  - `VT_E_OVERFLOW (-6)` – Pufferüberlauf
  - `VT_E_NOACT (-8)` – Kommando im aktuellen Zustand nicht möglich
  - `VT_E_NO_INSTANCE (-21)` – Keine VT-Client-Instanz verfügbar
  - `VT_E_ISO_INSTANCE_INVALID (-129)` – Verbindungsinstanz ungültig
  - `VT_E_NOT_ALIVE (-130)` – Instanz gültig, aber VT nicht aktiv
- **Adapterschnittstellen**: Die Verwendung von unidirektionalen Adaptern (AUDI) ermöglicht eine lose Kopplung zwischen dem Wertgeber und dem Baustein. Der alte und neue Wert können so in getrennten FBs verwaltet werden.
- **Einschränkungen**: Der Befehl unterstützt keine String-Attribute.

## Zustandsübersicht
Der FB besitzt keine explizit dargestellte Zustandsmaschine. Die Ablaufsteuerung erfolgt ereignisgesteuert:
- Nach **INIT** wechselt er in einen bereiten Zustand.
- Ein weiteres Ereignis wird erst durch den angeschlossenen Adapter-Socket ausgelöst (E1 von u32ValueAttribute). Nach der Verarbeitung wird **CNF** gesendet.
- Der Baustein ist **nicht zustandsbehaftet** im Sinne einer wiederverwendbaren Sequenz; jeder Request wird einzeln abgearbeitet.

## Anwendungsszenarien
- **ISOBUS-VT-Anwendungen**: Ändern von Parametern eines virtuellen Terminals (z. B. Hintergrundfarbe, Beschriftung, Sichtbarkeit) zur Laufzeit.
- **Steuerung landwirtschaftlicher Geräte**: Dynamisches Anpassen von Attributen wie Maschineneinstellungen oder Diagnosedaten.
- **Implementierung von ISO 11783-6 Workouts**: Nachbildung der Kommandostruktur „Change Attribute“ aus dem Standard.

## Vergleich mit ähnlichen Bausteinen
- **Q_Attribute** (ohne AUDI): Bietet die gleiche Kernfunktionalität, jedoch ohne Adapter-Schnittstellen. Der neue Wert muss hier direkt als Dateneingang übergeben werden und es erfolgt keine Rückmeldung des alten Werts. **Q_Attribute_AUDI** erweitert diesen Baustein um eine flexible, adapterbasierte Wertübergabe und die Rückgabe des alten Werts, was die Wiederverwendbarkeit und Kapselung erhöht.

## Fazit
**Q_Attribute_AUDI** ist ein spezialisierter Funktionsblock für ISOBUS-Anwendungen, der das sichere und standardkonforme Ändern von Attributen ermöglicht. Durch die adapterbasierte Schnittstelle für Attributwerte wird eine hohe Modularität erreicht, und die Ausgabe des alten Werts erlaubt eine einfache Nachverfolgung von Änderungen. Der Baustein ist ideal für komplexe VT-Implementierungen, bei denen Werte aus unterschiedlichen Quellen stammen oder in separaten Logikeinheiten verwaltet werden.