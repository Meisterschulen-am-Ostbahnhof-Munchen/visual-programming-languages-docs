# UDINT_AUDI_GT


![UDINT_AUDI_GT](./UDINT_AUDI_GT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **UDINT_AUDI_GT** führt einen Vergleich zweier Werte durch und gibt das Ergebnis aus, ob der erste Wert größer als der zweite ist. Er ist speziell für den Einsatz mit **Adapter-Schnittstellen** konzipiert, die eine flexible Kopplung mit unterschiedlichen Datenquellen und -senken ermöglichen. Der Baustein kapselt den IEC 61131-3 Vergleichsbaustein `F_GT` und erweitert ihn um eine adapterbasierte Ein- und Ausgabe.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar |
|------|-------|-----------|
| REQ  | Event | Service Request – löst den Vergleich aus |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine eigenen Ereignis-Ausgänge. Das Ergebnis-Ereignis wird über den **Out-Adapter** (OUT) bereitgestellt (siehe Adapter).

### **Daten-Eingänge**
| Name | Typ             | Kommentar     |
|------|----------------|---------------|
| IN1  | ANY_ELEMENTARY | Erster Vergleichswert (größer als ?) |

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenen Daten-Ausgänge. Das Vergleichsergebnis wird über den **Out-Adapter** (OUT) ausgegeben (siehe Adapter).

### **Adapter**
| Name | Typ      | Richtung | Kommentar |
|------|----------|----------|-----------|
| IN2  | `adapter::types::unidirectional::AUDI` | Socket | Zweiter Vergleichswert (Eingabe) |
| OUT  | `adapter::types::unidirectional::AX`   | Plug   | Ergebnisausgabe: `IN1 > IN2` |

Der Adapter `AUDI` liefert den zweiten Wert (`D1`) und ein zugehöriges Ereignis (`E1`).  
Der Adapter `AX` erwartet das Ergebnis (`D1`) und ein Ereignis (`E1`) zur Weiterleitung.

## Funktionsweise
1. Ein **Ereignis** am Eingang `REQ` oder ein **Ereignis über den Socket IN2** (E1) löst die Verarbeitung aus.
2. Der interne Vergleichsbaustein `F_GT` vergleicht den Datenwert von `IN1` mit dem Datenwert von `IN2` (über den Socket).
3. Das Ergebnis (TRUE/FALSE) wird über den Datenport `OUT.D1` des Plug `OUT` ausgegeben.
4. Gleichzeitig wird ein **Bestätigungsereignis** am Plug `OUT.E1` erzeugt, das signalisiert, dass das Ergebnis gültig ist.

Die Verbindung der inneren Logik ist im FBNetzwerk fest verdrahtet:  
- `IN1` → `F_GT.IN1`  
- `IN2.D1` → `F_GT.IN2`  
- `F_GT.OUT` → `OUT.D1`  
- Ereignisse: `REQ` oder `IN2.E1` → `F_GT.REQ`; `F_GT.CNF` → `OUT.E1`

## Technische Besonderheiten
- **Adapterbasierte Kommunikation**: Der Baustein verwendet standardisierte unidirektionale Adapter (`AUDI` und `AX`), die eine lose Kopplung zwischen den verbundenen Komponenten ermöglichen.
- **Flexible Datentypen**: `IN1` ist vom Typ `ANY_ELEMENTARY`, daher können verschiedene elementare Datentypen (BOOL, INT, UDINT, REAL etc.) verwendet werden. Der interne Vergleich erfolgt typsicher durch `F_GT`.
- **Zwei Auslösemöglichkeiten**: Der Vergleich kann sowohl über den Ereigniseingang `REQ` als auch über das vom Socket `IN2` kommende Ereignis gestartet werden.
- **Keine zustandsbehaftete Logik**: Der Baustein arbeitet rein kombinatorisch nach jedem Ereignis.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Sein Verhalten ist rein ereignisgesteuert und funktional: Auf jedes ankommende Ereignis (REQ oder IN2.E1) wird einmalig der Vergleich ausgeführt und das Ergebnis über den OUT-Adapter ausgegeben.

## Anwendungsszenarien
- **Vergleich in heterogenen Steuerungsystemen**: Einsatz in Systemen, bei denen unterschiedliche Datenquellen (z. B. Sensoren, Buskoppler) über Adapter angebunden werden.
- **Grenzwertüberwachung**: Prüfung, ob ein Messwert (IN1) einen Sollwert (IN2) überschreitet.
- **Steuerung von Ausgängen**: Verknüpfung des Ergebnisses mit Aktoren über den OUT-Adapter, z. B. zum Aktivieren eines Alarms oder einer Stellgröße.
- **Modulare Komposition**: Integration in komplexe Adapterketten, bei denen die Vergleichsfunktion als Zwischenbaustein dient.

## Vergleich mit ähnlichen Bausteinen
- **IEC 61131-3 Standard `F_GT`**: Ist reiner Datenvergleich ohne Adapter und erwartet direkte Dateneingänge. `UDINT_AUDI_GT` kapselt diesen Standardbaustein und erweitert ihn um adapterbasierte Ein-/Ausgabe.
- **Adapterbasierte Vergleichsbausteine**: Es existieren weitere Varianten (z. B. `UDINT_AUDI_LT`, `UDINT_AUDI_EQ`), die analog aufgebaut sind, aber andere Vergleichsoperationen ausführen.
- **Komfort-Vorteil**: Der Anwender muss sich nicht um die interne Ereignissteuerung kümmern; die Adapter übernehmen die Synchronisation der Werte und Ereignisse.

## Fazit
Der Funktionsblock **UDINT_AUDI_GT** bietet eine flexible und standardisierte Möglichkeit, einen „Größer-als“-Vergleich in Adapter-basierten Automatisierungsprojekten durchzuführen. Durch die Kapselung des IEC-Vergleichsbausteins und die Verwendung standardisierter Schnittstellen eignet er sich besonders für modulare und wiederverwendbare Steuerungsarchitekturen.