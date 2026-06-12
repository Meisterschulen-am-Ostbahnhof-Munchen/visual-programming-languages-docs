# AD_SHL


![AD_SHL](./AD_SHL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_SHL** führt eine bitweise Linksverschiebung (Shift Left) eines Eingangswertes durch. Er ist als generischer Baustein konzipiert, der über Adapter-Schnittstellen kommuniziert und beliebige ganzzahlige Datentypen (ANY_INT) unterstützt. Die eigentliche Verschiebeoperation wird intern durch einen vordefinierten Baustein `F_SHL` realisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung | Mit-Parameter |
|----------|---------------|---------------|
| `UPDATE` | Aktualisiert die Schiebeanzahl und startet die Berechnung. | `N` |

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Das Ereignis zur Weitergabe des Ergebnisses erfolgt über den Adapter `OUT` (Ereignis `OUT.E1`).

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| `N` | `ANY_INT` | Anzahl der Bit-Positionen, um die verschoben werden soll. |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Das Ergebnis der Verschiebung wird über den Adapter `OUT` (Daten `OUT.D1`) bereitgestellt.

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket | `IN` | `adapter::types::unidirectional::AD` | Empfängt den zu verschiebenden Wert über den Adapter-Kanal. |
| Plug | `OUT` | `adapter::types::unidirectional::AD` | Stellt das Ergebnis der Linksverschiebung zur Verfügung. |

## Funktionsweise
Der FB arbeitet als kompositiver Funktionsblock, der die eigentliche Operation an den Baustein `F_SHL` delegiert. Intern wird folgende Logik umgesetzt:

1. **Ereignisauslösung**  
   - Ein eingehendes Ereignis von `UPDATE` oder vom Adapter `IN.E1` triggert den Eingang `REQ` des internen `F_SHL`-Bausteins.
   - Der Wert von `N` wird direkt an den `F_SHL.N`-Eingang übergeben.
   - Der über den Adapter `IN` bereitgestellte Datenwert (`IN.D1`) wird an den `F_SHL.IN`-Eingang weitergeleitet.

2. **Berechnung**  
   Der interne Baustein `F_SHL` (Typ `iec61131::bitwiseOperators::F_SHL`) führt die bitweise Linksverschiebung des Eingangswertes um die in `N` angegebene Anzahl durch.

3. **Ausgabe**  
   Das Ergebnis der Berechnung (`F_SHL.OUT`) wird auf den Datenausgang des Plug-Adapter `OUT.D1` übertragen. Gleichzeitig signalisiert das Ereignis `F_SHL.CNF` dem Plug-Adapter (`OUT.E1`) das Vorliegen des neuen Ergebnisses.

Der Baustein ist ereignisgesteuert: Jedes Eintreffen eines gültigen Ereignisses (entweder extern über `UPDATE` oder vom Socket-Adapter `IN`) löst eine vollständige Berechnung aus.

## Technische Besonderheiten
- **Adapter-Schnittstelle**  
  Anstelle fester Ein- und Ausgänge verwendet der FB Adapter (`IN` als Socket, `OUT` als Plug), was eine flexible Anbindung in verschiedenen Architekturkontexten ermöglicht.
- **Generischer Datentyp**  
  Der Parameter `N` ist als `ANY_INT` deklariert, sodass der Baustein mit unterschiedlichen ganzzahligen Typen (z. B. `INT`, `DINT`, `LINT`) arbeiten kann, solange der interne `F_SHL` diese unterstützt.
- **Kombinierte Ereignissteuerung**  
  Sowohl das externe Ereignis `UPDATE` als auch das vom Socket-Adapter empfangene Ereignis `IN.E1` können die Berechnung anstoßen. Dies ermöglicht sowohl zyklische als auch datengetriebene Aktualisierungen.
- **Lizenzierung**  
  Der Baustein ist unter der Eclipse Public License 2.0 lizenziert und als generischer FB konzipiert.

## Zustandsübersicht
Der FB ist als **kompositives Netzwerk** realisiert und besitzt keinen eigenen internen Zustandsautomaten (ECC). Die Ablaufsteuerung wird vollständig durch die Ereignisverbindungen innerhalb des Netzwerks und den verwendeten `F_SHL`-Baustein bestimmt. Eine explizite Zustandsmaschine ist nicht erforderlich.

## Anwendungsszenarien
- **Bitmanipulation in der Steuerungstechnik**  
  Verschieben von Bitmustern zur Maskierung, Skalierung oder Kodierung von Signalen.
- **Datenaufbereitung in Kommunikationsprotokollen**  
  Anpassung von Datenworten durch Linksverschiebung, z. B. für serielle Schnittstellen oder Bussysteme.
- **Arithmetische Berechnungen**  
  Multiplikation mit Zweierpotenzen durch Linksverschiebung, insbesondere in rechenzeitkritischen Umgebungen.

## Vergleich mit ähnlichen Bausteinen
- **Direkter `F_SHL`-Baustein**  
  Der interne `F_SHL` bietet die gleiche Funktionalität, jedoch ohne Adapter-Schnittstelle. `AD_SHL` kapselt diesen Baustein und erweitert ihn um eine adapterbasierte Anbindung, was die Wiederverwendung in modularen Systemen erleichtert.
- **Adapterbasierte Rechenbausteine**  
  Ähnliche Konzepte existieren für andere bitweise Operationen (z. B. `AD_SHR`, `AD_AND`). `AD_SHL` spezifiziert die Linksverschiebung und kann in einer Bibliothek adaptergekoppelter Logikbausteine verwendet werden.

## Fazit
Der Funktionsblock `AD_SHL` realisiert eine bitweise Linksverschiebung mittels eines gekapselten `F_SHL`-Bausteins und stellt die gesamte Funktionalität über eine standardisierte Adapter-Schnittstelle zur Verfügung. Durch die generische Auslegung und die flexible Ereignissteuerung eignet er sich für vielfältige Anwendungen in der IEC-61499-basierten Automatisierungstechnik. Seine kompositive Struktur macht ihn wartbar und leicht erweiterbar.