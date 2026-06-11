# AD_TO_AX


![AD_TO_AX](./AD_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AD_TO_AX` dient als Composite-FB zur Umwandlung eines AD-Adapters (Datenwort – DWORD) in einen AX-Adapter (Boolescher Wert – BOOL). Er kapselt einen Vergleichsmechanismus, der prüft, ob der anliegende DWORD-Wert ungleich Null ist, und das Ergebnis als BOOL an den Ausgangsadapter weiterleitet. Der Baustein vereinfacht die Adapterkommunikation in Steuerungssystemen, indem er die Signaltypen zwischen verschiedenen Komponenten umsetzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine eigenständigen Ereignis-Eingänge. Das Ereignis wird über den Socket-Adapter `AD_IN` bereitgestellt (siehe Abschnitt **Adapter**).

### **Ereignis-Ausgänge**
Keine eigenständigen Ereignis-Ausgänge. Das Ergebnisereignis wird über den Plug-Adapter `AX_OUT` bereitgestellt (siehe Abschnitt **Adapter**).

### **Daten-Eingänge**
Keine eigenständigen Daten-Eingänge. Die Eingangsdaten werden über den Socket-Adapter `AD_IN` bereitgestellt (siehe Abschnitt **Adapter**).

### **Daten-Ausgänge**
Keine eigenständigen Daten-Ausgänge. Die Ausgangsdaten werden über den Plug-Adapter `AX_OUT` bereitgestellt (siehe Abschnitt **Adapter**).

### **Adapter**
| Adapter | Richtung | Typ | Kommentar |
|---------|----------|-----|-----------|
| `AD_IN` | Socket | `adapter::types::unidirectional::AD` | DWORD-Eingangsadapter – liefert Ereignis und DWORD-Daten. |
| `AX_OUT` | Plug | `adapter::types::unidirectional::AX` | BOOL-Ausgangsadapter – gibt Ereignis und Boolesches Ergebnis aus. |

Die Adapter folgen dem unidirektionalen Muster und stellen jeweils einen Ereignisausgang (`E1`) und einen Datenausgang (`D1`) zur Verfügung:
- **AD_IN.E1** → initiiert die Verarbeitung.
- **AD_IN.D1** → enthält den DWORD-Quellwert.
- **AX_OUT.E1** → signalisiert das Ende der Verarbeitung.
- **AX_OUT.D1** → enthält den Booleschen Ergebniswert.

## Funktionsweise
Der FB `AD_TO_AX` ist als Composite FB realisiert. Er enthält eine Instanz des Vergleichsbausteins `F_NE` („ungleich“) aus der IEC 61131-Bibliothek.

1. Ein eingehendes Ereignis auf `AD_IN.E1` triggert den Eingang `F_NE.REQ`.
2. Der Baustein `F_NE` vergleicht den Wert von `AD_IN.D1` mit dem konstanten Wert `DWORD#0`.
3. Das Vergleichsergebnis (BOOL) wird am Ausgang `F_NE.OUT` bereitgestellt.
4. Über eine Datenverbindung gelangt dieses Ergebnis an `AX_OUT.D1`.
5. Gleichzeitig signalisiert `F_NE.CNF` das Ende der Berechnung und triggert `AX_OUT.E1`.

Somit wird aus einem DWORD-Wert ein BOOL-Wert abgeleitet:  
- `DWORD = 0` → Ausgabe `FALSE`  
- `DWORD ≠ 0` → Ausgabe `TRUE`

## Technische Besonderheiten
- **Composite-FB**: Der Baustein besteht aus einem internen Netzwerk, das die eigentliche Logik abbildet – dies erleichtert die Wiederverwendung und Kapselung.
- **Verwendung von `F_NE`**: Der eingesetzte Vergleichsbaustein aus der IEC 61131-Bibliothek ist standardisiert und plattformunabhängig.
- **Adapterbasierte Kommunikation**: Statt einzelner Ein-/Ausgänge werden Adapter verwendet, was die strukturierte Verbindung zu anderen Adapter-kompatiblen Bausteinen ermöglicht.
- **Unidirektionale Adapter**: Sowohl Eingangs- als auch Ausgangsadapter sind unidirektional, d.h. sie transportieren Daten und Ereignisse nur in eine Richtung – dies vermeidet Rückkopplungen und vereinfacht das Design.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten, da er ausschließlich aus einer logischen Verknüpfung besteht. Der interne Ablauf ist ereignisgesteuert:
- **Ruhezustand**: Warten auf ein Ereignis am Eingang `AD_IN.E1`.
- **Ausführung**: Nach dem Ereignis erfolgt die Berechnung durch `F_NE` und die Weiterleitung des Ergebnisses – dies geschieht in einem Schritt ohne Zwischenzustände.

## Anwendungsszenarien
- **Adapterkonvertierung**: Ein System arbeitet mit DWORD-Adaptern, ein angeschlossenes Modul erwartet jedoch BOOL-Signale. Der `AD_TO_AX`-Baustein übernimmt die Umwandlung.
- **Schwellwertabfrage**: Prüfung, ob ein DWORD-Wert von Null abweicht (z.B. Aktivsignal, Zählerstand > 0).
- **Signalaufbereitung**: Vereinfacht die Integration von Sensoren oder Aktoren, deren Ausgang als DWORD codiert ist, in boolesche Steuerungslogiken.

## Vergleich mit ähnlichen Bausteinen
- **Direkter `DWORD_TO_BOOL`-Konverter**: Ein solcher FB würde typischerweise nur die Datenkonvertierung durchführen, aber keine Adapterstruktur und kein Ereignis-Handling bieten. `AD_TO_AX` hingegen kapselt sowohl Ereignis- als auch Datenpfade in Adaptern.
- **Allgemeine Adapterkonverter**: Es gibt ähnliche Bausteine für andere Datentypen (z.B. `AD_TO_AX` für WORD, INT etc.). Der vorliegende FB ist speziell auf die Umwandlung DWORD → BOOL ausgelegt.
- **Composite vs. Basic FB**: Als Composite-FB ist der Baustein leicht anpassbar, da das interne Netzwerk bei Bedarf modifiziert werden kann.

## Fazit
Der Funktionsblock `AD_TO_AX` bietet eine elegante und standardisierte Möglichkeit, einen DWORD-Adaptersignale in einen BOOL-Adapter umzuwandeln. Durch die Nutzung des etablierten Vergleichsbausteins `F_NE` ist die Logik robust und nachvollziehbar. Die Adapterstruktur erleichtert die Integration in modulare Automatisierungssysteme und fördert die Wiederverwendbarkeit. Der FB ist besonders geeignet für Szenarien, in denen eine ereignisgesteuerte Umwandlung von digitalen Werten in boolesche Zustände erforderlich ist.