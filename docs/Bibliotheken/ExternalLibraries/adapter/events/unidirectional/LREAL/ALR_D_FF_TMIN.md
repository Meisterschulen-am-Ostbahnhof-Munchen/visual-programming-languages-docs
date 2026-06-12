# ALR_D_FF_TMIN


![ALR_D_FF_TMIN](./ALR_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_D_FF_TMIN** realisiert einen taktflankengesteuerten Data-Latch-Flipflop (D-Flipflop) mit einer minimalen Verzögerungszeit zwischen zwei aufeinanderfolgenden Ereignisausgängen (Minimum inter-disposal Time). Er ermöglicht das latchen eines Datenwerts bei Empfang eines Ereignisses und stellt sicher, dass der Ausgangsereignis-Stoß nicht schneller als ein definierbares Zeitintervall erfolgt. Dies ist besonders nützlich, um nachgeschaltete Systeme vor Überlastung zu schützen oder zeitliche Mindestabstände in der Ereigniskommunikation einzuhalten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ   | Kommentar                                          |
|----------|-------|----------------------------------------------------|
| INIT     | EInit | Initialisierungsanforderung; setzt die Mindestzeit `Tmin` |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Kommentar                                |
|----------|-------|------------------------------------------|
| INITO    | EInit | Bestätigung der erfolgreichen Initialisierung |

### **Daten-Eingänge**
| Name | Typ  | Kommentar                                   |
|------|------|---------------------------------------------|
| Tmin | TIME | Minimale Wartezeit zwischen zwei EO-Ereignissen |

### **Daten-Ausgänge**
*Keine eigenen Datenausgänge vorhanden – der gelatchte Wert wird über den Adapterausgang bereitgestellt.*

### **Adapter**
| Adapter | Richtung | Typ         | Kommentar                         |
|---------|----------|-------------|-----------------------------------|
| I       | Socket   | ALR (unidirektional) | Eingangswert (`D1`) und Takt (`E1`) |
| Q       | Plug     | ALR (unidirektional) | Ausgangswert (`D1`) und Quittung (`E1`) |

Der Adapter `ALR` (unidirectional) besitzt einen Ereigniseingang `E1` und einen Dateneingang `D1` (Socket-Seite) bzw. einen Ereignisausgang `E1` und Datenausgang `D1` (Plug-Seite). – Die genaue Semantik von `E1` und `D1` ist anwendungsspezifisch; hier dient `E1` als Takt und `D1` als der zu latchende Datenwert.

## Funktionsweise
Nach der Initialisierung (INIT) arbeitet der Baustein wie folgt:

1. **Ereignis am Eingangsadapter `I.E1`** löst den Latch-Vorgang aus. Der aktuelle Wert `I.D1` wird intern übernommen.
2. Der gelatchte Wert wird sofort am Ausgangsadapter `Q.D1` ausgegeben.
3. Gleichzeitig wird ein Ereignis `Q.E1` ausgelöst – jedoch erst, wenn seit dem letzten Ausgangsereignis mindestens die Zeit `Tmin` vergangen ist.  
   Falls ein weiteres `I.E1`-Ereignis innerhalb der Wartezeit eintrifft, wird es ignoriert (bzw. erst nach Ablauf von `Tmin` verarbeitet). Die minimale Verzögerung wird durch den internen Funktionsblock `E_D_FF_ANY_TMIN` realisiert.

Der Datenwert wird also bei jedem gültigen Takt aktualisiert, die Ausgabe des Ereignisses jedoch zeitlich gestreckt.

## Technische Besonderheiten
- **Zusammengesetzter FB**: Der Baustein ist als Composite-FB realisiert und verwendet intern den FB `iec61499::events::E_D_FF_ANY_TMIN`. Die Logik des eigentlichen Flipflops und die Zeitsteuerung wird dort gekapselt.
- **Universelles Zeitintervall**: `Tmin` kann zur Laufzeit über INIT gesetzt werden und ist nicht fest vorgegeben.
- **Gepufferte Ereignisse**: Da die Ereignisausgabe verzögert wird, können ankommende Taktereignisse während der Wartezeit verloren gehen, es sei denn, der interne FB puffert sie (hier nicht spezifiziert). Typisch ist ein einfaches Ignorieren.
- **Adapterbasierte Schnittstelle**: Die Verwendung von Adaptern ermöglicht eine flexible Verschaltung in modularen Steuerungsanwendungen, ohne dass die Anschlüsse fest verdrahtet werden müssen.

## Zustandsübersicht
Der Baustein besitzt keine expliziten Zustände, sondern arbeitet ereignisgesteuert:

- **Idle**: Warten auf `I.E1` (nach INIT).  
- **Latchen**: Bei `I.E1` wird der Datenwert übernommen und `Q.E1` nach Ablauf von `Tmin` ausgelöst.  
- **Blockiert**: Während `Tmin` noch nicht abgelaufen ist, werden weitere `I.E1` ignoriert.  
- Nach Ablauf der Wartezeit kehrt der Baustein in den idle-Zustand zurück.

## Anwendungsszenarien
- **Entprellung von Sensorsignalen**: Ein Sensor liefert Ereignisse schneller als die nachfolgende Steuerung verarbeiten kann. `Tmin` legt den Mindestabstand fest.
- **Pulsweitenbegrenzung**: Sicherstellung, dass Aktorsteuerungen nicht zu schnell hintereinander geschaltet werden (z. B. Ventile, Motoren).
- **Taktsynchronisation**: Wenn ein Datenwert mit einem asynchronen Takt gelatcht und erst nach einer definierten Totzeit weitergegeben werden soll.
- **Sicherheitsfunktionen**: Verhindern von „Rapid-Fire“-Befehlen in kritischen Anwendungen.

## Vergleich mit ähnlichen Bausteinen
- **E_D_FF_ANY_TMIN**: Ist der interne Baustein – er bietet die gleiche Funktionalität, jedoch ohne die Adapter-Schnittstelle. `ALR_D_FF_TMIN` kapselt diesen in eine anwendungsfreundlichere, adapterbasierte Form.
- **Standard IEC 61499 D-Flipflops**: Diese haben oft keine zeitliche Steuerung der Ausgangsereignisse. Der hier beschriebene FB erweitert sie um die `Tmin`-Verzögerung.
- **FB mit TON/Timer**: Ein reiner Timer würde nur zeitverzögert auslösen, aber keinen Datenwert halten. Die Kombination mit einem Latch ist spezifisch.

## Fazit
Der Funktionsblock `ALR_D_FF_TMIN` vereint die Eigenschaften eines D-Flipflops mit einer einstellbaren Mindestzeit zwischen Ereignisausgaben. Durch die Adaptertechnik und die einfache Initialisierung lässt er sich flexibel in IoT-, Automatisierungs- oder Steuerungsumgebungen einsetzen. Besonders geeignet ist er für Anwendungen, die eine zeitliche Entkopplung zwischen Datenerfassung und Ereignisweitergabe erfordern.