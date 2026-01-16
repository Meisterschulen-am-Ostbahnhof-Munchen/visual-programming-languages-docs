# AX_PULSE

* * * * * * * * * *
## Einleitung
Der AX_PULSE ist ein Funktionsblock, der einen Impuls über einen AX-Adapter ausgibt.

## Schnittstellenstruktur

### **Adapter**
**Sockets (Eingänge):**
- **REQ** (adapter::types::unidirectional::AX): Trigger.

**Plugs (Ausgänge):**
- **PULSE** (adapter::types::unidirectional::AX): Impulsausgang.

## Funktionsweise
Bei REQ wird PULSE kurzzeitig aktiv.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Impuls.

## Anwendungsszenarien
Signalisierung.

## Vergleich mit ähnlichen Bausteinen
- **E_PULSE**

## Fazit
Adapter-basierter Impuls-Baustein.
