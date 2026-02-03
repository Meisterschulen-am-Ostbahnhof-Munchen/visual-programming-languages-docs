# SchieberAuxOutStruct

```{index} single: SchieberAuxOutStruct
```

* * * * * * * * * *
## Einleitung
Der Datenbaustein `SchieberAuxOutStruct` definiert eine Struktur zur Konfiguration der visuellen Darstellung eines AUX-Ausgabeelements. Er wird verwendet, um sowohl das anzuzeigende Bild als auch dessen Hintergrundfarbe festzulegen. Dieser Baustein ist Teil einer Funktionalität zur Steuerung von Bildschirmanzeigen, typischerweise in landwirtschaftlichen oder mobilen Arbeitsmaschinen.

## Schnittstellenstruktur
Der Baustein ist ein strukturierter Datentyp (STRUCT) und besitzt keine Ereignis- oder Adapterschnittstellen. Er besteht ausschließlich aus Daten-Elementen.

### **Daten-Eingänge**
Die Struktur selbst besitzt keine Eingänge im herkömmlichen Sinne, da es sich um einen Datentyp handelt. Ihre Elemente werden beim Anlegen einer Instanz dieses Typs mit Werten belegt.

### **Daten-Ausgänge**
Die Struktur selbst besitzt keine Ausgänge. Sie definiert die folgenden internen Datenfelder:

| Name | Datentyp | Initialwert | Kommentar |
| :--- | :--- | :--- | :--- |
| `Picture` | `UINT` | `ID_NULL` | u16ObjId für das anzuzeigende Bild. |
| `u8Colour` | `USINT` | `COLOR_WHITE` | Hintergrundfarbe des AUX-Elements. |

## Funktionsweise
Die `SchieberAuxOutStruct` ist eine reine Datenhaltungsstruktur. Sie kapselt die beiden Parameter `Picture` (Bild-ID) und `u8Colour` (Hintergrundfarbe), die gemeinsam benötigt werden, um die visuellen Eigenschaften eines AUX-Ausgabefeldes zu beschreiben. Die Initialwerte stellen einen definierten Grundzustand sicher: ein leeres Bild (`ID_NULL`) auf weißem Hintergrund (`COLOR_WHITE`).

## Technische Besonderheiten
*   **Initialisierung:** Die Struktur verwendet vordefinierte Konstanten (`ID_NULL`, `COLOR_WHITE`) aus importierten Namensräumen für die Initialwerte. Dies gewährleistet Konsistenz und vereinfacht die Wartung.
*   **Typisierung:** Die explizite Typisierung (`UINT` für die Bild-ID, `USINT` für die Farbe) ermöglicht eine strenge Prüfung durch den Compiler und erhöht die Zuverlässigkeit.
*   **Verwendung:** Dieser STRUCT wird typischerweise als Datentyp für Ein- oder Ausgänge von Funktionsblöcken (FBs) verwendet, die mit grafischen Benutzeroberflächen oder Anzeigegeräten interagieren.

## Zustandsübersicht
Da es sich um einen passiven Datentyp handelt, besitzt die `SchieberAuxOutStruct` keinen internen Zustandsautomaten. Ihr "Zustand" wird vollständig durch die aktuell gespeicherten Werte in `Picture` und `u8Colour` definiert.

## Anwendungsszenarien
Primär dient dieser Baustein zur Parametrierung von Anzeigeelementen in ISOBUS-kompatiblen Terminals (UT). Konkrete Anwendungen sind:
*   Konfiguration von Schiebereglern oder Statusanzeigen in einer Bedienoberfläche.
*   Dynamische Änderung von Symbolen und deren Hintergrund in Abhängigkeit vom Maschinenzustand (z.B. Warnung, Aktivität, Fehler).
*   Standardisierung des Datenaustauschs zwischen Steuerungslogik und Visualisierungs-Funktionsblöcken.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken, die eine aktive Logik enthalten, ist `SchieberAuxOutStruct` ein reiner Datentyp. Ähnliche STRUCTs im gleichen Kontext könnten z.B. `SchieberAuxInStruct` für Eingabeparameter oder allgemeinere `DisplayElementStruct`-Bausteine sein, die möglicherweise zusätzliche Eigenschaften wie Position oder Größe enthalten. Dieser Baustein ist spezifisch auf die Kombination von Bild und Hintergrundfarbe zugeschnitten.

## Fazit
Die `SchieberAuxOutStruct` ist eine essentielle, wiederverwendbare Datenkomponente für Anzeigeanwendungen in der 4diac-IDE. Durch die Kapselung der relevanten Parameter in einem strukturierten Typ fördert sie klare Schnittstellen, verbessert die Lesbarkeit des Codes und reduziert Fehler bei der Parameterübergabe. Ihre Verwendung mit initialisierten Standardwerten und importierten Konstanten folgt bewährten Software-Engineering-Praktiken.