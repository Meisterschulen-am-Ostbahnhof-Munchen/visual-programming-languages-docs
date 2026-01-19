# AX_OR_6

```{index} single: AX_OR_6
```

<img width="963" height="403" alt="image" src="https://github.com/user-attachments/assets/69d7eff1-3373-49b6-877a-d54f351451e1" />

* * * * * * * * * *
## Einleitung
Der AX_OR_6 ist ein generischer Funktionsblock zur Berechnung einer logischen ODER-Verknüpfung mit sechs Eingängen. Der Baustein dient zur Verarbeitung von booleschen Signalen in Automatisierungssystemen und gibt das Ergebnis der ODER-Operation über einen Adapterausgang aus.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereigniseingänge vorhanden

### **Ereignis-Ausgänge**
Keine Ereignisausgänge vorhanden

### **Daten-Eingänge**
Keine Dateneingänge vorhanden

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden

### **Adapter**
**Eingangsadapter:**
- **IN1** - ODER-Eingang 1 (Typ: adapter::types::unidirectional::AX)
- **IN2** - ODER-Eingang 2 (Typ: adapter::types::unidirectional::AX)
- **IN3** - ODER-Eingang 3 (Typ: adapter::types::unidirectional::AX)
- **IN4** - ODER-Eingang 4 (Typ: adapter::types::unidirectional::AX)
- **IN5** - ODER-Eingang 5 (Typ: adapter::types::unidirectional::AX)
- **IN6** - ODER-Eingang 6 (Typ: adapter::types::unidirectional::AX)

**Ausgangsadapter:**
- **OUT** - ODER-Ergebnis (Typ: adapter::types::unidirectional::AX)

## Funktionsweise
Der Funktionsblock berechnet kontinuierlich die logische ODER-Verknüpfung aller sechs Eingangssignale. Das Ausgangssignal ist TRUE (wahr), wenn mindestens einer der sechs Eingänge TRUE ist. Nur wenn alle sechs Eingänge FALSE (falsch) sind, wird der Ausgang ebenfalls FALSE.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse 'GEN_AX_OR'
- Verwendet unidirektionale AX-Adapter für die Signalübertragung
- Sechs unabhängige Eingänge für flexible Anwendungen
- Echtzeitfähige Verarbeitung ohne Ereignissteuerung

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand und arbeitet stateless. Die Ausgabe wird kontinuierlich basierend auf den aktuellen Eingangswerten berechnet.

## Anwendungsszenarien
- Sicherheitskreise mit mehreren Not-Aus-Tastern
- Überwachungssysteme mit mehreren Sensoren
- Steuerungslogik mit alternativen Aktivierungsbedingungen
- Verknüpfung mehrerer Zustandsmeldungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren ODER-Bausteinen mit weniger Eingängen bietet AX_OR_6 eine höhere Flexibilität durch sechs separate Eingänge. Die ausschließliche Verwendung von Adaptern statt konventioneller Daten-Ein-/Ausgänge ermöglicht eine modulare Systemarchitektur.

Vergleich mit [OR_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_6.md)

## Fazit
Der AX_OR_6 ist ein spezialisierter Logikbaustein für Anwendungen, die eine ODER-Verknüpfung mit mehreren Eingängen erfordern. Durch die Adapter-basierte Schnittstelle eignet er sich besonders für modulare Systemdesigns und ermöglicht eine klare Trennung der Signalwege.