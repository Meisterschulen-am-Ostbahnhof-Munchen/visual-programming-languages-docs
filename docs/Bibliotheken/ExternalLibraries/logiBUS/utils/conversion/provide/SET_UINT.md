# SET_UINT


![SET_UINT](./SET_UINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock SET_UINT dient dazu, einen UINT-Wert, der an einem Dateneingang anliegt, in eine als InOut-Parameter deklarierte Variable zu schreiben. Diese einfache aber grundlegende Operation erlaubt es, Daten aus dem FB‑Kontext in eine externe oder referenzierte Variable zu kopieren.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Beschreibung               |
|------|-------|----------------------------|
| REQ  | Event | Normaler Ausführungsbefehl  |

### **Ereignis-Ausgänge**
| Name | Typ   | Beschreibung                   |
|------|-------|--------------------------------|
| CNF  | Event | Bestätigung der Ausführung      |

### **Daten-Eingänge**
| Name | Typ  | Initialwert | Beschreibung                |
|------|------|-------------|-----------------------------|
| IN   | UINT | 0           | Wert, der geschrieben wird  |

### **Daten-Ausgänge**
*Keine separaten Ausgänge vorhanden.* Der Zielwert wird über die InOut‑Variable `OUT` bereitgestellt.

### **Adapter**
*Keine Adapter.*

## Funktionsweise
Die Verarbeitung erfolgt in einem Schritt:
1. Ein Ereignis am Eingang `REQ` triggert die Ausführung des Algorithmus.
2. Der Algorithmus kopiert den Wert des Dateneingangs `IN` in die InOut‑Variable `OUT`.
3. Nach Abschluss wird das Ereignis `CNF` ausgegeben.

Die InOut‑Variable `OUT` wird dabei als referenzierte Variable interpretiert – der FB schreibt direkt in die Speicherstelle, die beim Aufruf mit der `OUT`‑Schnittstelle verbunden ist.

## Technische Besonderheiten
- **InOut‑Variable als Ziel:** Der FB verwendet eine InOut‑Variable (`OUT`) anstelle eines reinen Ausgangs. Dadurch kann der Baustein in Aufrufumgebungen (z. B. innerhalb von Ressourcen oder anderen FBs) direkt auf eine bestehende Variable zugreifen und diese überschreiben.
- **Einzeiliger Algorithmus:** Die Zuweisung `OUT := IN` erfolgt in einem einzigen ST‑Befehl; es werden keine weiteren Berechnungen oder Zwischenspeicherungen durchgeführt.
- **Keine Zustandsautomaten:** Der FB besitzt nur einen Einstiegszustand (`REQ`), eine Zustandsänderung oder Schleifen sind nicht vorgesehen.

## Zustandsübersicht
| Zustand | Aktion | Ausgabe |
|---------|--------|---------|
| REQ     | `OUT := IN` | CNF     |

Der FB bleibt nach Ausführung in einem impliziten Endzustand; er ist für jede neue `REQ`‑Anforderung erneut bereit.

## Anwendungsszenarien
- **Setzen eines Konfigurationswertes:** Ein Sollwert oder Parameter (z. B. ein Schwellwert in einem Regelungsbaustein) wird von außen hereingegeben und in die entsprechende interne Variable geschrieben.
- **Kopieren von UINT‑Daten an eine zentrale Speicherstelle:** In einer Steuerung kann `SET_UINT` verwendet werden, um Messwerte oder Berechnungsergebnisse in einen globalen Datenbaustein zu übertragen.
- **Austausch von Daten zwischen FBs:** Über die InOut‑Variable können zwei verschiedene FBs auf die gleiche Variable zugreifen – der `SET_UINT`‑FB dient dabei dem gezielten Überschreiben.

## Vergleich mit ähnlichen Bausteinen
- **SET_BOOL / SET_INT / SET_*:** Diese Bausteine unterscheiden sich lediglich im verwendeten Datentyp. Die Funktionsweise – „Wert von IN nach OUT schreiben“ – ist identisch.
- **MOVE (z. B. `MOVE` in IEC 61131-3):** Eine allgemeine Kopierfunktion, die jedoch meist als Standardfunktion (ohne eigenes Event‑Interface) realisiert ist. Der `SET_UINT`‑FB bietet die explizite Ereignissteuerung für die Ausführung.
- **Sonderfall InOut:** Im Gegensatz zu reinen Ausgangsbausteinen erlaubt `SET_UINT` den direkten Zugriff auf die Zielvariable, was bei der Datenweitergabe über Hierarchiegrenzen hinweg Vorteile bringt.

## Fazit
Der FB `SET_UINT` ist ein minimaler, aber nützlicher Baustein, um einen UINT‑Wert zielgerichtet in eine referenzierte Variable zu schreiben. Seine einfache Struktur – ein Ereignis löst eine Zuweisung aus – macht ihn besonders in Umgebungen nützlich, in denen ein explizites „Setzen“ einer Variable über ein Ereignis gefordert wird. Erfüllt er keine weiteren Bedingungen, ist er als Musterbaustein für ähnliche Datentyp‑spezifische Set‑Funktionen geeignet.