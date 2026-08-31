# AD_XOR_5

![AD_XOR_5](./AD_XOR_5.svg)

* * * * * * * * * *

## Einleitung

Der **AD_XOR_5** ist ein generischer Funktionsblock zur bitweisen XOR (exklusives ODER)-Verknüpfung von 5 Eingangswerten vom Typ `DWORD` (32-Bit-Bitmuster (Doppelwort)). Im Gegensatz zur booleschen Verknüpfung einzelner Wahrheitswerte (wie bei den `AX_XOR`-Bausteinen) wird hier jedes einzelne Bit des Datenworts unabhängig verknüpft.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**

Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge vorhanden

### **Adapter**

**Eingangsadapter:**

- **IN1**: XOR (exklusives ODER)-Eingang 1 (Typ: adapter::types::unidirectional::AD)
- **IN2**: XOR (exklusives ODER)-Eingang 2 (Typ: adapter::types::unidirectional::AD)
- **IN3**: XOR (exklusives ODER)-Eingang 3 (Typ: adapter::types::unidirectional::AD)
- **IN4**: XOR (exklusives ODER)-Eingang 4 (Typ: adapter::types::unidirectional::AD)
- **IN5**: XOR (exklusives ODER)-Eingang 5 (Typ: adapter::types::unidirectional::AD)

**Ausgangsadapter:**

- **OUT**: XOR (exklusives ODER)-Ergebnis (Typ: adapter::types::unidirectional::AD)

## Funktionsweise

Sobald an einem der 5 Eingangsadapter (`IN1` … `IN5`) ein Ereignis eintrifft, verknüpft der Baustein die Bitmuster aller 5 Eingänge bitweise mit **XOR (exklusives ODER)** und schreibt das Ergebnis auf den Ausgangsadapter `OUT`. Als Startwert der Verknüpfung dient das neutrale Element (alle Bits gelöscht / 0 (Nullelement der XOR-Verknüpfung)), sodass bei nur einem tatsächlich angeschlossenen Eingang dessen Wert unverändert durchgereicht wird.

Nur wenn sich das neu berechnete Ergebnis vom aktuell auf `OUT` gehaltenen Wert unterscheidet, wird `OUT` neu beschrieben und dessen Adapter-Event gesendet (siehe „Änderungserkennung" unten).

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AD_XOR`) definiert und deckt über den GenericClassName-Mechanismus alle Aritäten (2 bis 8 Eingänge) derselben Grundlogik ab.
- **Bitweise Verknüpfung**: Anders als bei den booleschen `AX_XOR`-Bausteinen wird hier jedes Bit des `DWORD`-Datenworts einzeln verknüpft, nicht nur ein einzelner Wahrheitswert.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `unidirectional::AD` – die Daten fließen nur vom Socket zum Plug.
- **Normkonformität**: Der Baustein implementiert die Verknüpfung gemäß IEC 61499-2 / IEC 61131-3.

## Zustandsübersicht

Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AD_XOR_5 keine internen Zustände. Die Ausgabe wird bei jedem eingehenden Ereignis direkt aus den aktuellen Eingangswerten neu berechnet.

## Anwendungsszenarien

- **Bitmasken-Verknüpfung**: Kombinieren mehrerer Statusregister oder Flag-Bytes vom Typ `DWORD` zu einem Gesamtergebnis.
- **Signalaggregation**: Zusammenführen mehrerer `DWORD`-Datenquellen (z. B. aus verschiedenen Modulen) über eine gemeinsame XOR (exklusives ODER)-Verknüpfung.
- **Diagnose- und Statusauswertung**: Prüfen von Bitmustern auf gemeinsame oder unterschiedliche gesetzte Bits.

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu `AX_XOR_5`, der einzelne boolesche Wahrheitswerte verknüpft, arbeitet `AD_XOR_5` auf dem vollständigen Bitmuster eines `DWORD`-Werts. Verglichen mit dem Standard-Baustein [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md) verwendet `AD_XOR_5` Adapter-basierte Schnittstellen anstelle direkter Daten-/Ereignisein-/ausgänge, was eine flexiblere Integration in Adapter-basierte Systemarchitekturen ermöglicht.

- **[`AD_XOR_5_UNGATED`](AD_XOR_5_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der **AD_XOR_5** bietet eine zuverlässige, generische Implementierung der bitweisen XOR (exklusives ODER)-Funktion für `DWORD`-Werte mit Adapter-basierten Schnittstellen. Seine generische Natur macht ihn vielseitig einsetzbar in Automatisierungsprojekten, die nach IEC 61499-Standard entwickelt werden und mehrere Bitmuster desselben Datentyps kombinieren müssen.
