# Tastend

```{index} single: Tastend
```

<img width="662" height="233" alt="image" src="https://github.com/user-attachments/assets/26789397-647c-4c13-b28d-5752fd19880c" />

* * * * * * * * * *

## Einleitung
Diese Übung beschäftigt sich mit der Erstellung und Verwendung eines Sub-Applikationstyps in 4diac-IDE. Der Funktionsbaustein "tastend" dient als Sub-Applikation und implementiert eine unidirektionale Adapterverbindung zwischen Eingangs- und Ausgangsadaptern.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: tastend
- **Typ**: SubAppType
- **Verwendete interne FBs**: Keine internen FBs vorhanden
- **Funktionsweise**: Der Sub-Baustein "tastend" stellt eine Adapterverbindung zwischen einem Eingangs-Adapter (IN) und einem Ausgangs-Adapter (OUT) her. Beide Adapter verwenden den Typ "adapter::types::unidirectional::AX" und ermöglichen eine unidirektionale Datenübertragung.

## Programmablauf und Verbindungen
Der Sub-Baustein "tastend" verfügt über folgende Schnittstellen:
- **Eingangsadapter**: IN (Typ: adapter::types::unidirectional::AX)
- **Ausgangsadapter**: OUT (Typ: adapter::types::unidirectional::AX)

Die Verbindung erfolgt direkt vom Eingangsadapter IN zum Ausgangsadapter OUT. Diese Konfiguration ermöglicht eine einfache Weiterleitung von Signalen oder Daten durch den Sub-Baustein.

**Schwierigkeitsgrad**: Einfach
**Benötigte Vorkenntnisse**: Grundkenntnisse in 4diac-IDE, Verständnis von Adapterverbindungen und Sub-Applikationen
**Start der Übung**: Der Sub-Baustein kann in größere Applikationen integriert und über die definierten Adapterschnittstellen angesteuert werden.

## Zusammenfassung
Die Übung "tastend" demonstriert die Erstellung eines einfachen Sub-Applikationstyps mit Adapterverbindungen. Sie zeigt die grundlegende Struktur von Sub-Bausteinen in 4diac-IDE und deren Integration in größere Steuerungsapplikationen durch standardisierte Adapterschnittstellen.


## Zugehörige Übungen

* [Uebung_103](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c.md)
* [Uebung_103c2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c2.md)

